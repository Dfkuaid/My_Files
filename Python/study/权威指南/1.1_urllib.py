#!/usr/bin/python3
from urllib.request import urlopen

html = urlopen('https://www.baidu.com')
print(html.read())
