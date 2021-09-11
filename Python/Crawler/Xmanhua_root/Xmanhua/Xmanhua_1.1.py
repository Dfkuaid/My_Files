from selenium import webdriver
from bs4 import BeautifulSoup
from lxml import etree
import requests
import os
import time

def Pic_save(path,url):
    respone = requests.get(url)
    with open(path,'wb') as f:
        f.write(respone.content)

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

def Get_ver(path):
    with open(path + 'update.txt','r') as f:
        line = f.readline()
        line_num = line.split()
        a = line_num[0]

    return a

def Update(path,num):
    s = str(num)
    with open(path + 'update.txt','w') as f:
        f.write(s)

def Create(path):
    if not os.path.exists(path):
        os.makedirs(path)
    else:
        print('目标文件夹已存在， 3秒后进入更新状态')
        return True
    return False

def each(url,path_z):
    browser = webdriver.Firefox()
    browser.get(url)
    browser.implicitly_wait(3)

    html_each = requests.get(url)
    html_x = etree.HTML(html_each.content)
    soup = BeautifulSoup(html_each.content,'lxml')

    name = html_x.xpath('//div[@class="reader-title"]/a[3]/text()')
    os.mkdir(path_z + name[0])
    path_s = path_z + name[0] + '/'

    pageNum_s = (soup.find('a',attrs={'class':'reader-bottom-page'})).get_text()
    # print(pageNum_s)
    pageNum_st = ''
    flag = 0
    for i in range(len(pageNum_s)):
        if is_number(pageNum_s[i]) == False:
            flag = 0
        if flag == 1:
            pageNum_st = pageNum_st + pageNum_s[i]
        if pageNum_s[i] == '/':
            flag = 1
    # print(pageNum_st)
    pageNum = int(pageNum_st)
    # print(pageNum)

    for i in range(pageNum):
        # print(i)
        if i + 1 >= 100:
            pageNum_c = '0' + str(i + 1)
        elif i + 1 < 10:
            pageNum_c = '000' + str(i + 1)
        else:
            pageNum_c = '00' + str(i + 1)
        l = list(url)
        l[len(l) - 1] = ''
        url_n = ''
        for j in range(len(l)):
            url_n = url_n + l[j]
        page_url = url_n + '-p' + str(i + 1) + '/'
        browser.get(page_url)
        browser.implicitly_wait(3)
        time.sleep(0.5)
        pic_url = browser.find_element_by_xpath("//div[@class='item']/img").get_attribute('src')
        #print(pic_url)
        #print(path_s + pageNum_c + '.jpg')
        Pic_save(path_s + pageNum_c + '.jpg',pic_url)

    print(name[0] + '保存完毕！')
	
    browser.quit()

def mulu(base_url,path_a):
    url_list = []
    
    html = requests.get(base_url)
    soup = BeautifulSoup(html.content,'lxml')
    liTag = soup.find('div',attrs={'class':'detail-list-form-con'})
    liTags = liTag.find_all('a')
    name_a1 = (soup.find('p',attrs={'class':'detail-info-title'})).get_text()
    l = list(name_a1)
    for i in range(len(l)):
        if l[i] == ' ':
            l[i] = ''
    name_a = ''
    for i in range(len(l)):
        name_a = name_a + l[i]
    print(name_a)

    ver = 0
    path_z = path_a + name_a + '/'
    if Create(path_a + name_a):
        time.sleep(3)
        ver = Get_ver(path_z)
    
    i = 0
    for li in liTags:
        url_list.append("https://www.xmanhua.com" + li['href'])
        i = i + 1
    
    if i - int(ver) == 0:
        print('无可更新章节，3秒后自动退出')
        time.sleep(3)
        return

    print("各章节地址获取完成！共" + str(i) + "话,需更新" + str(i - int(ver)) + "话")
    
    j = i - int(ver) - 1
    while j >= 0:
        # print(url_list[j])
        each(url_list[j],path_z)
        Update(path_z,i - j)
        # print(j)
        j = j - 1
    
    
    
def main():
    base_url = str(input('请输入漫画首页地址： \n'))
    path_a = './Download/'
    mulu(base_url,path_a)
    print("Finished saving!")

if __name__ == '__main__':
    main()
