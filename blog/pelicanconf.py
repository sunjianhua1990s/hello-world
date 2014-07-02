#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = u'sunjianhua'
SITENAME = u"Build Our World"
SITEURL = 'http://www.linuxyu.com'

TIMEZONE = 'Asia/Shanghai'
DEFAULT_DATE_FORMAT = '%Y-%m-%d %H:%M:%S'

DEFAULT_LANG = u'zh'

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None

# Blogroll
LINKS =  (('Google', 'https://www.google.com/ncr'),
          ('Python', 'http://python.org/'),
          ('Pelican', 'http://docs.getpelican.com/'),
         )

# Social widget
SOCIAL = (('Github', 'https://github.com/sunjianhua1990s'),
          (u'微博', ''),
          (u'知乎', ''),
          (u'豆瓣', ''),
         )


DEFAULT_PAGINATION = 5


# Uncomment following line if you want document-relative URLs when developing
RELATIVE_URLS = True

THEME = 'tuxlite_tbs'
#THEME = "pelican-themes/elegant"

DISQUS_SITENAME = u'sunjianhua1990s'

#设置路径
PLUGIN_PATH = u'pelican-plugins'
PLUGINS = ["sitemap"]
## 配置sitemap 插件
SITEMAP = {
    "format": "xml",
    "priorities": {
        "articles": 0.7,
        "indexes": 0.5,
        "pages": 0.3,
    },
    "changefreqs": {
        "articles": "monthly",
        "indexes": "daily",
        "pages": "monthly",
    }
}

GOOGLE_ANALYTICS = 'UA-52496177-1'

GOOGLE_CUSTOM_SEARCH_SIDEBAR = ''



STATIC_PATHS = [u"img"]

GITHUB_URL = 'https://github.com/sunjianhua1990s'
ARCHIVES_URL = 'archives.html'

#打造漂亮的URL
ARTICLE_URL = 'pages/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'pages/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

#使用目录名作为文章的分类名
USE_FOLDER_AS_CATEGORY = True
#使用文件名作为文章或页面的slug（url）
FILENAME_METADATA = '(?P<slug>.*)'
#页面的显示路径和保存路径，推荐下面的方式
ARTICLE_URL = '{category}/{slug}.html'
ARTICLE_SAVE_AS = ARTICLE_URL
PAGE_URL = '{slug}.html'
PAGE_SAVE_AS = PAGE_URL
CATEGORY_URL = '{slug}/index.html'
CATEGORY_SAVE_AS = CATEGORY_URL
TAG_URL = 'tag/{slug}.html'
TAG_SAVE_AS = TAG_URL
TAGS_SAVE_AS = 'tag/index.html'

