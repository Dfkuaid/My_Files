#!/usr/bin/python3
from bs4 import BeautifulSoup
from urllib.request import urlopen
from urllib.error import HTTPError

def get_title(url):
    try:
        html = urlopen(url)
    except HTTPError:
        return None
    try:
        soup = BeautifulSoup(html.read(), 'html.parser')
        title = soup.body.h1
    except AttributeError as e:
        return None
    return title

def MAIN():
    url = input('Please enter the url:')
    title = get_title(url)
    if title == None:
        print('Title could not found.')
    else:
        print(title)

if __name__ == '__main__':
    MAIN()
