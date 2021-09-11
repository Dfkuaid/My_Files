from selenium import webdriver
from bs4 import BeautifulSoup
from lxml import etree
import requests
import os
import time

url = 'http://www.xmanhua.com/m127243/#ipg3'
html_each = requests.get(url)
html_x = etree.HTML(html_each.content)
soup = BeautifulSoup(html_each.content,'lxml')

name = html_x.xpath('//div[@class="reader-title"]/a[3]/text()')
print(name[0])

s = input('键入"Enter"以退出')