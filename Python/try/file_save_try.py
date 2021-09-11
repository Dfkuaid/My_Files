import os
import requests
import urllib.request

# headers = {'User-Agent':'Mozilla/5.0 3578.98 Safari/537.36'}

name = 'try'
b = os.getcwd()
os.mkdir(b + '\\' + name)

respone = requests.get('http://img.mljzmm.com/comic/14339/057/0001.jpg')
with open(b + '\\' + name + '\\' + 'a.jpg','wb') as f:
    f.write(respone.content)
