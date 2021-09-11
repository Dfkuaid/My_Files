from selenium import webdriver

fireFoxOptions = webdriver.FirefoxOptions()
fireFoxOptions.set_headless()
brower = webdriver.Firefox()
brower.get('http://www.baidu.com')
print(brower.page_source)
brower.close()
