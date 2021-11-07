## #1.0 安装与启用

### #1.1 安装

直接采用 `pip` 安装即可：

``` bash
pip install selenium
```

对于不同的浏览器采用不同的驱动：

- Firefox 浏览器驱动：[geckodriver](https://github.com/mozilla/geckodriver/releases)
- Chrome 浏览器驱动：[chromedriver](https://sites.google.com/a/chromium.org/chromedriver/home) , [taobao备用地址](https://npm.taobao.org/mirrors/chromedriver)
- PhantomJS 浏览器驱动：[phantomjs](http://phantomjs.org/)

windows 下需要**把浏览器驱动放入系统路径中，或者直接告知selenuim的驱动路径**，个人**不建议**使用 Chrome，因为驱动需要随着浏览器的升级而升级，不如 Firefox 一劳永逸。

### #1.2 启用

``` python
from selenium import webdriver


driver = webdriver.Firefox()   # Firefox浏览器
# driver = webdriver.Firefox("驱动路径")

driver = webdriver.Chrome()    # Chrome浏览器

driver = webdriver.PhantomJS()   # PhantomJS

# 打开网页
driver.get(url) # 打开url网页 比如 driver.get("http://www.baidu.com")
```

## #2.0 查找与获取元素

### #2.1 查找符合要求的元素

``` python
find_element_by_id()
find_element_by_name()
find_element_by_class_name()
find_element_by_tag_name()
find_element_by_link_text()
find_element_by_partial_link_text()
find_element_by_xpath()
find_element_by_css_selector()
```

以上是根据条件获取第一个满足条件的元素信息，将 `element` 变为 `elements` 即可获取所有符合条件的元素，返回一个数组。

### #2.2 获取所需要的元素

上面我们已经得到了所有满足条件的元素信息（位置），于是下一步便是要得到我们所需要的元素内容。

对于元素文本，我们可以用 `text()` 得到单个元素的文本，如果要得到列表中所有元素的文本，可以采用 `get_attribute()` 进行获取，比如下面这个栗子：

``` html
<a herf="#modal" class="text-box">修改</a>
```

- 如果用 `get_attribute(textContent)` 可以得到标签之间的文本内容，即 `修改`；
- 或 `get_attribute(innerHTML)` 可以得到当前标签（不包括）以内的完整 HTML；

- 如果用 `get_attribute(outerHTML)` 可以得到包括当前标签的全部信息，即

  ``` html
  <a herf="#modal" class="text-box">修改</a>
  ```

同样，我们也可以获取 `a` 的任意一项属性：

- 采用 `get_attribute("herf")` 得到的是 `#modal`；
- 采用 `get_attribute("class")` 得到的是 `text-box`；

其他属性依次类推。

## #3.0 浏览器控制

### #3.1 一些基础操作

``` python
from selenium import webdriver

driver = webdriver.Firefox()
driver.get("https://www.baidu.com")

driver.find_element_by_id("kw").clear()
driver.find_element_by_id("kw").send_keys("selenium")
driver.find_element_by_id("su").click()

# driver.quit()
```

上面代码就是进入 `www.baidu.com` 自动搜索 `selenium`，`clear()` 为清空文本，`send_keys()` 为模拟键盘输入文本，`click()` 为模拟鼠标点击。

