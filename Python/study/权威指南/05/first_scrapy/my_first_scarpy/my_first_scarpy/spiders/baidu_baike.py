from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule

class Article_Spider(CrawlSpider):
    name = 'articles'
    allowed_domains = ['en.wikipedia.org']
    start_urls = ['https://en.wikipedia.org/wiki/Wiki']
    rules = [
        Rule(LinkExtractor(allow = '^(/wiki/)((?!:).)*$'),
            callback = 'parse_items', follow = True)
    ]

    def parse_items(self, response):
        print("Getin")
        print(response.url)
        title = response.css('h1::text').extract_first()
        url = response.url
        text = response.xpath('//div[@id="mw-content-text"]//text()').extract()
        last_updated = response.css('li#footer-info-lastmod::text').extract_first()
        last_updated = last_updated.replace(' This page was last edited on ', '')
        print('Title is: {}'.format(title))
        print('Text is: {}'.format(text))
        print('Updated on: {}'.format(last_updated))
