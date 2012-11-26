#!/usr/bin/python

import os
import http.client
import json
import sys
import string
from urllib.parse import urlencode
from functools import reduce

DATA_PATH = 'data' + os.sep

url = 'search.twitter.com'
search_path = '/search.json?'

def load_sentiments(file_name="data"+os.sep+"sentiments.csv"):
    """Read the sentiment file and return a dictionary containing the sentiment
    score of each word, a value from -1 to +1.
    """
    sentiments = {}
    for line in open(file_name, encoding='utf8'):
        word, score = line.split(',')
        sentiments[word] = float(score.strip())
    return sentiments

class TweetSuperCrawler(object):
    """Grabs and processes tweets"""

    def __init__(self, keyword, result_number = 100, result_type = 'mixed', page = 5):
        self.keyword = keyword
        self.result_number = result_number
        self.result_type = result_type
        self.page = page

    def search(self):
        f = http.client.HTTPConnection(url)
        parameters = {'q': self.keyword, 'rpp': self.result_number, 'result_type': self.result_type, 'page': self.page}

        PATH = '%s%s' % (search_path, urlencode(parameters))

        try:
            f.request('GET', PATH)
            r = f.getresponse()
            data = r.read()
            f.close()
            try:
                result = json.loads(data.decode('utf8'))
                #Result in the format result['results'][i] = tweet, result['results'][i]['text'] = tweet text, result['results'][i]['from_user'] = user, result['results'][i]['id'] = tweet id in the form twitter.com/#!/user/status/id
            except ValueError:
                return None
            if 'results' not in result:
                return None
            return result['results']
        except:
            return None

    def analyze_tweet_sentiment(self, tweet):
        """ Return a number between -1 and +1 representing the degree of positive or
        negative sentiment in the given tweet, averaging over all the words in the
        tweet that have a sentiment score.

        If no words in the tweet have a sentiment score, returns None.
        """
        def tweet_words(tweet):
            """ Returns a list of words within a tweet """
            new = list(tweet)
            for x in new:
            	if x not in list(string.ascii_letters):
            		new[new.index(x)] = ' '
            new = ''.join(new)
            return new.split()

        average = None
        unknown_counter = 0
        word_list = tweet_words(tweet)
        word_list_feeling = list(word_sentiments.get(word) for word in word_list)
        for sentiment in word_list_feeling:
        	if sentiment == None:
        		unknown_counter += 1
        word_list_feeling = list(map(lambda x: 0 if x == None else x, word_list_feeling))
        if len(word_list_feeling) - unknown_counter == 0:
        	return
        else:
        	average = reduce(lambda x, y: x+y, word_list_feeling)/(len(word_list_feeling) - unknown_counter)
        return average

    def find_sentiments(self, tweets):
        overall_sentiment = 0
        num_tweets = 0
        tweets_and_sent = {}
        for i in range(len(tweets)):
            tweet_sentiment = self.analyze_tweet_sentiment(tweets[i]['text'])
            if tweet_sentiment:
                overall_sentiment += tweet_sentiment
                num_tweets += 1
                tweet_link = 'twitter.com/#!/{0}/status/{1}'.format(tweets[i]['from_user'], tweets[i]['id'])
                tweets_and_sent[tweet_link] = tweet_sentiment

        average_sentiment = overall_sentiment/num_tweets
        return {'avg': average_sentiment, 'indv': tweets_and_sent}

    def process(self):
        tweets = self.search()

        positive = 0
        negative = 0
        neutral = 0

        if tweets:
            sentiments = self.find_sentiments(tweets)
            tweets_and_sent = sentiments['indv']

            for tweet in tweets_and_sent:
                if tweets_and_sent[tweet] > 0:
                    positive += 1
                elif tweets_and_sent[tweet] < 0:
                    negative += 1
                else:
                    neutral += 1

            percent_pos = positive/(positive+negative+neutral)
            percent_neg = negative/(positive+negative+neutral)
            percent_neu = neutral/(positive+negative+neutral)

            return {'avg': sentiments['avg'], 'indv': tweets_and_sent, 'percent_pos': percent_pos, 'percent_neg': percent_neg, 'percent_neu': percent_neu}

        return 'Could not find a sentiment =('


def main():
    global word_sentiments
    word_sentiments = load_sentiments()

    input_value= input('What do you want to analyze? ')
    if input_value:
        crawler = TweetSuperCrawler(input_value)
        result = crawler.process()
        print('On a scale of -1 to 1, the nation of Twitter has a happiness rating of {0} about "{1}"'.format(str(result['avg'])[:5], input_value))
    else:
        print('You didn\'t input anything =(')

if __name__ == '__main__':
    main()


