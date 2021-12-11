#!/usr/bin/python3
from urllib.request import urlopen
from urllib.error import HTTPError
from bs4 import BeautifulSoup

def get_beautifulsoup(url):
    try:
        html = urlopen(url)
        bs = BeautifulSoup(html.read(), 'html.parser')
    except (HTTPError, AttributeError):
        return None
    return bs

def get_table(bs):
    try:
        with open('2.2.3.1_test.txt', mode = 'w') as f:
            f.write("\nchildren:\n")
            for child in bs.find('table', {'id' : 'giftList'}).children:
                f.write(str(child))
            f.write("\nnext_sibling:\n")
            for sibling in bs.find('table', {'id' : 'giftList'}).tr.next_siblings:
                f.write(str(sibling))
            f.write("\nparent and previous_sibling\n")
            f.write(bs.find('img', {'src' : '../img/gifts/img1.jpg'})
                    .parent.previous_sibling.get_text())
    except AttributeError:
        print('There is nothing.')

def MAIN():
    bs = get_beautifulsoup('http://pythonscraping.com/pages/page3.html')
    if bs == None:
        print('The page could not found.'); return
    get_table(bs)

if __name__ == '__main__':
    MAIN()
