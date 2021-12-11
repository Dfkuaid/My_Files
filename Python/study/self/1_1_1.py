import requests

hd = {'User-agent':'123'}
r = requests.get('http://www.baidu.com', headers=hd)
print(r.request.headers)

