import urllib.request
import re
import json
import os

def get_tickers():
    ticker_list = []
    url = 'http://en.wikipedia.org/w/api.php?format=json&action=query&titles=List_of_S%26P_500_companies&prop=revisions&rvprop=content'

    f = urllib.request.urlopen(url)
    data = json.loads(f.read().decode('utf8'))
    data = data['query']['pages']['2676045']['revisions'][0]
    for key in data:
        data = data[key]

    tickers = re.findall('{{NyseSymbol\|\w+}}', data)
    tickers2 = re.findall('{{NasdaqSymbol\|\w+}}', data)

    for ticker in tickers:
        ticker_list.append(ticker[13:-2])
    for ticker in tickers2:
        ticker_list.append(ticker[15:-2])

    return ticker_list

def main():
    ticker_list = get_tickers()
    if os.path.exists('E:\Dropbox\Projects\Quant\data\sp500_tickers.txt'):
        os.remove('E:\Dropbox\Projects\Quant\data\sp500_tickers.txt')
    f = open('E:\Dropbox\Projects\Quant\data\sp500_tickers.txt', 'w', encoding = 'utf8')
    for ticker in ticker_list:
        f.write(ticker + '\n')
    f.close()

if __name__ == '__main__':
    main()
