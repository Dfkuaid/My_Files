from selenium import webdriver
from bs4 import BeautifulSoup
import requests
import os
import time

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
 
    return False

url = 'http://www.xmanhua.com/m127243/'
html = requests.get(url)
soup = BeautifulSoup(html.content,'lxml')

pageNum_s = (soup.find('a',attrs={'class':'reader-bottom-page'})).get_text()
print(pageNum_s)

pageNum_st = ''
flag = 0
for i in range(len(pageNum_s)):
    if is_number(pageNum_s[i]) == False:
        flag = 0
    if flag == 1:
        pageNum_st = pageNum_st + pageNum_s[i]
    if pageNum_s[i] == '/':
        flag = 1
print(pageNum_st)

s = input('键入"Enter"以退出')