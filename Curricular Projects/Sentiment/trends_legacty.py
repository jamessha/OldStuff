"""Visualizing Twitter Sentiment Across America"""

import string
import re
from data import word_sentiments, load_tweets
from geo import us_states, geo_distance, make_position, longitude, latitude
from maps import draw_state, draw_name, draw_dot, wait
from ucb import main, trace, interact, log_current_line


# Phase 1: The feelings in tweets

def make_tweet(text, time, lat, lon):
    """Return a tweet, represented as a python dictionary.    

    text -- A string; the text of the tweet, all in lowercase
    time -- A datetime object; the time that the tweet was posted
    lat -- A number; the latitude of the tweet's location
    lon -- A number; the longitude of the tweet's location
    """
    return {'text': text, 'time': time, 'latitude': lat, 'longitude': lon}

def tweet_words(tweet):
    """Return a list of words in the tweet.
    
    Arguments:
    tweet -- a tweet abstract data type.
    
    Return 1 value:
     - The list of words in the tweet.
    """
    text = tweet['text']
    return extract_words(text)

def tweet_location(tweet):
    """Return a position (see geo.py) that represents the tweet's location."""
    latitude = tweet['latitude']
    longitude = tweet['longitude']
    return make_position(latitude, longitude)

def tweet_string(tweet):
    """Return a string representing the tweet."""
    return '"{0}" @ {1}'.format(tweet['text'], tweet_location(tweet))

def extract_words(text):
    """Return the words in a tweet, not including punctuation.

    >>> extract_words('anything else.....not my job')
    ['anything', 'else', 'not', 'my', 'job']
    >>> extract_words('i love my job. #winning')
    ['i', 'love', 'my', 'job', 'winning']
    >>> extract_words('make justin # 1 by tweeting #vma #justinbieber :)')
    ['make', 'justin', 'by', 'tweeting', 'vma', 'justinbieber']
    >>> extract_words("paperclips! they're so awesome, cool, & useful!")
    ['paperclips', 'they', 're', 'so', 'awesome', 'cool', 'useful']
    """
    """
    ascii = []
    i = 0
    while i < len(string.ascii_letters): #creates a list of all ascii characters
    	if string.ascii_letters[i] not in ascii:
    		ascii.append(string.ascii_letters[i])
    	i += 1
    i2 = 0
    temp = ''
    temp2 = text
    final = []
    while len(temp2) > 1:
    	i2 += 1
    	if i2 >= len(temp2) - 1: #taking care of the end - i2 is last character
    		if temp2[i2] in ascii: #if last character is valid
    			final.append(temp2)
    			temp2 = []
    		elif temp2[i2-1] in ascii: #if last character is invalid
    			final.append(temp2[:-1])
    			temp2 = []
    		else: #if more than one invalid characters at the end
    			if temp2[:-2] != '':
    				final.append(temp2[:-2])
    			temp2 = []
    	elif temp2[i2-1] not in ascii: #finds an invalid character
    		temp = temp2[:i2-1] #creates temporary list with everything up to invalid character
    		temp2 = temp2[i2:] #new list used contains everything past the invalid character
    		if temp != '': #tests to see if it finds two invalid characters in a row
    			final.append(temp)
    		i2 = 0 #resets the counter since the new list used resets
    	assert i2 < 1000 #safety so memory doesn't run dry
    return final
    """
    new = list(text)
    for x in new:
    	if x not in list(string.ascii_letters):
    		new[new.index(x)] = ' '
    new = ''.join(new)
    return new.split()


def get_word_sentiment(word):
    """Return a number between -1 and +1 representing the degree of positive or
    negative feeling in the given word. 

    Return None if the word is not in the sentiment dictionary.
    (0 represents a neutral feeling, not an unknown feeling.)
    
    >>> get_word_sentiment('good')
    0.875
    >>> get_word_sentiment('bad')
    -0.625
    >>> get_word_sentiment('winning')
    0.5
    >>> get_word_sentiment('Berkeley')  # Returns None
    """
    return word_sentiments.get(word, None)

def analyze_tweet_sentiment(tweet):
    """ Return a number between -1 and +1 representing the degree of positive or
    negative sentiment in the given tweet, averaging over all the words in the
    tweet that have a sentiment score. 

    If there are words that don't have a sentiment score, leave them 
    out of the calculation. 

    If no words in the tweet have a sentiment score, return None.
    (do not return 0, which represents neutral sentiment).

    >>> positive = make_tweet('i love my job. #winning', None, 0, 0)
    >>> round(analyze_tweet_sentiment(positive), 5)
    0.29167
    >>> negative = make_tweet("Thinking, 'I hate my job'", None, 0, 0)
    >>> analyze_tweet_sentiment(negative)
    -0.25
    >>> no_sentiment = make_tweet("Go bears!", None, 0, 0)
    >>> analyze_tweet_sentiment(no_sentiment)
    """
    from functools import reduce
    average = None
    unknown_counter = 0
    text = tweet['text']
    word_list = extract_words(text)
    word_list_feeling = list(get_word_sentiment(x) for x in word_list)
    for x in word_list_feeling:
    	if x == None:
    		unknown_counter += 1
    word_list_feeling = list(map(lambda x: 0 if x == None else x, word_list_feeling))
    if len(word_list_feeling) - unknown_counter == 0:
    	return
    else:
    	average = reduce(lambda x, y: x+y, word_list_feeling)/(len(word_list_feeling) - unknown_counter)
    return average

#@main
def print_sentiment(text='Are you virtuous or verminous?'):
    """Print the words in text, annotated by their sentiment scores.

    For example, to print each word of a sentence with its sentiment:

    # python3 trends.py "computer science is my favorite!"
    """
    words = extract_words(text.lower())
    assert words, 'No words extracted from "' + text + '"'
    layout = '{0:>' + str(len(max(words, key=len))) + '}: {1}'
    for word in extract_words(text.lower()):
        print(layout.format(word, get_word_sentiment(word)))
        

# Phase 2: The geometry of maps

def find_centroid(polygon):
    """Find the centroid of a polygon.

    http://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon
    
    polygon -- A list of positions, in which the first and last are the same

    Returns: 3 numbers; centroid latitude, centroid longitude, and polygon area

    Hint: If a polygon has 0 area, return its first position as its centroid

    >>> p1, p2, p3 = make_position(1, 2), make_position(3, 4), make_position(5, 0)
    >>> triangle = [p1, p2, p3, p1]  # First vertex is also the last vertex
    >>> find_centroid(triangle)
    (3.0, 2.0, 6.0)
    >>> find_centroid([p1, p3, p2, p1])
    (3.0, 2.0, 6.0)
    >>> find_centroid([p1, p2, p1])
    (1, 2, 0)
    """
    summation_centroid_x = 0
    summation_centroid_y = 0
    summation_area = 0
    i = 0
    while i < len(polygon)-1:
    	summation_centroid_x += ((polygon[i][0] + polygon[i+1][0])*(polygon[i][0]*polygon[i+1][1] - polygon[i+1][0]*polygon[i][1]))
    	summation_centroid_y += ((polygon[i][1] + polygon[i+1][1])*(polygon[i][0]*polygon[i+1][1] - polygon[i+1][0]*polygon[i][1]))
    	summation_area += (polygon[i][0]*polygon[i+1][1] - polygon[i+1][0]*polygon[i][1])
    	i += 1
    area = summation_area/2
    if area != 0:
    	centroid_x = summation_centroid_x/6/area
    	centroid_y = summation_centroid_y/6/area
    else:
    	area = 0
    	centroid_x = polygon[0][0]
    	centroid_y = polygon[0][1]
    return (centroid_x, centroid_y, abs(area))

def find_center(shapes):
    """Compute the geographic center of a state, averaged over its shapes.

    The center is the average position of centroids of the polygons in shapes,
    weighted by the area of those polygons.
    
    Arguments:
    shapes -- a list of polygons

    >>> ca = find_center(us_states['CA'])  # California
    >>> round(latitude(ca), 5)
    37.25389
    >>> round(longitude(ca), 5)
    -119.61439

    >>> hi = find_center(us_states['HI'])  # Hawaii
    >>> round(latitude(hi), 5)
    20.1489
    >>> round(longitude(hi), 5)
    -156.21763
    """
    x_sum = 0
    y_sum = 0
    area_sum = 0
    centroid_list = list(map(find_centroid, shapes))
    for x in centroid_list:
    	x_sum += x[0]*x[2]
    	y_sum += x[1]*x[2]
    	area_sum += x[2]
    centroid_x = x_sum/area_sum
    centroid_y = y_sum/area_sum
    return make_position(centroid_x, centroid_y)


# Uncomment this decorator during Phase 2.
#@main
def draw_centered_map(center_state='TX', n=10):
    """Draw the n states closest to center_state.
    
    For example, to draw the 20 states closest to California (including California):

    # python3 trends.py CA 20
    """
    us_centers = {n: find_center(s) for n, s in us_states.items()}
    center = us_centers[center_state.upper()]
    dist_from_center = lambda name: geo_distance(center, us_centers[name])
    for name in sorted(us_states.keys(), key=dist_from_center)[:int(n)]:
        draw_state(us_states[name])
        draw_name(name, us_centers[name])
    draw_dot(center, 1, 10)  # Mark the center state with a red dot
    wait()


# Phase 3: The mood of the nation

def find_closest_state(tweet, state_centers):
    """Return the name of the state closest to the given tweet's location.
    
    Use the geo_distance function (already provided) to calculate distance 
    in miles between two latitude-longitude positions.

    Arguments:
    tweet -- a tweet abstract data type
    state_centers -- a dictionary from state names to positions

    >>> us_centers = {n: find_center(s) for n, s in us_states.items()}
    >>> sf = make_tweet("Welcome to San Francisco", None, 38, -122)
    >>> ny = make_tweet("Welcome to New York", None, 41, -74)
    >>> find_closest_state(sf, us_centers)
    'CA'
    >>> find_closest_state(ny, us_centers)
    'NJ'
    """
    position_tweet = make_position(tweet['latitude'], tweet['longitude'])
    for x in state_centers:
    	state_name = x
    	loc = state_centers[x]
    	temp_dis = geo_distance(position_tweet, loc)
    	try: distance
    	except NameError:
    		distance = temp_dis
    		state = state_name
    	else:
    		if temp_dis < distance:
    			distance = temp_dis
    			state = state_name
    return state
    	
    
    

def group_tweets_by_state(tweets):
    """Return a dictionary that aggregates tweets by their nearest state center.

    The keys of the returned dictionary are state names, and the values are
    lists of tweets that appear closer to that state center than any other.
    
    tweets -- a sequence of tweet abstract data types    

    >>> sf = make_tweet("Welcome to San Francisco", None, 38, -122)
    >>> ny = make_tweet("Welcome to New York", None, 41, -74)
    >>> ca_tweets = group_tweets_by_state([sf, ny])['CA']
    >>> tweet_string(ca_tweets[0])
    '"Welcome to San Francisco" @ (38, -122)'
    """
    tweets_by_state = {}
    us_centers = {n: find_center(s) for n, s in us_states.items()}
    for x in tweets:
    	state = find_closest_state(x, us_centers)
    	if state not in tweets_by_state:
    		tweets_by_state[state] = [x]
    	else:
    		tweets_by_state[state].append(x)
    return tweets_by_state

def calculate_average_sentiments(tweets_by_state):
    """Calculate the average sentiment of the states by averaging over all 
    the tweets from each state that have a sentiment value. Return the result
    as a dictionary from state names to average sentiment values.
   
    If a state has no tweets with sentiment values, leave it out of the
    dictionary entirely.  Do not include a states with no tweets, or with tweets
    that have no sentiment, as 0.  0 represents neutral sentiment, not unknown
    sentiment.

    tweets_by_state -- A dictionary from state names to lists of tweets
    """
    averaged_state_sentiments = {}
    for state in tweets_by_state: 
    	no_sent_tweet = 0 #number of tweets that contain no sentiment
    	total_sent = 0 #summation of sentiment values
    	for tweet in tweets_by_state[state]:
    		temp_sent = analyze_tweet_sentiment(tweet) #finds the sentiment of one tweet
    		if temp_sent != None:
    			total_sent += temp_sent #includes tweets with neutral sentiment
    		else:
    			no_sent_tweet += 1 #excludes tweets with no sentiment
    	if total_sent == None or (len(tweets_by_state[state]) - no_sent_tweet) == 0:
    		average_sent = 0 #marks the state for exclusion
    	else:
    		average_sent = total_sent/(len(tweets_by_state[state]) - no_sent_tweet) #average sentiment of a state excluding tweets with no sentiment
    	if state not in averaged_state_sentiments and average_sent != 0:
    		averaged_state_sentiments[state] = average_sent #if state has a sentiment, it gets placed into the dictionary
    return averaged_state_sentiments

def draw_state_sentiments(state_sentiments={}):
    """Draw all U.S. states in colors corresponding to their sentiment value.
    
    Unknown state names are ignored; states without values are colored grey.
    
    state_sentiments -- A dictionary from state strings to sentiment values
    """
    for name, shapes in us_states.items():
        sentiment = state_sentiments.get(name, None)
        draw_state(shapes, sentiment)
    for name, shapes in us_states.items():
        center = find_center(shapes)
        if center is not None:
            draw_name(name, center)

# Uncomment this decorator during Phase 3.
#@main
def draw_map_for_term(term='my job'):
    """
    Draw the sentiment map corresponding to the tweets that match term.
    
    term -- a word or phrase to filter the tweets by.  
    
    To visualize tweets containing the word "obama":
    
    # python3 trends.py obama
    
    Some term suggestions:
    New York, Texas, sandwich, my life, justinbieber
    """
    tweets = load_tweets(make_tweet, term)
    tweets_by_state = group_tweets_by_state(tweets)
    state_sentiments = calculate_average_sentiments(tweets_by_state)
    draw_state_sentiments(state_sentiments)
    for tweet in tweets:
        draw_dot(tweet_location(tweet), analyze_tweet_sentiment(tweet))
    wait()
