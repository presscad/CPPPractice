# -*- coding:utf-8 -*-

import urllib
import urllib2
import cookielib
import re
import webbrowser

class OrderCar:
    def login(self):
        #登录的URL
        self.loginURL = "http://haijia.bjxueche.net/Login.aspx?LoginOut=true"
        #代理IP地址，防止自己的IP被封禁
        self.proxyURL = 'http://120.193.146.97:843'
        #登录POST数据时发送的头部信息
        self.loginHeaders =  {
            'Host':'haijia.bjxueche.net',
            'User-Agent' : 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36',
            'Referer' : 'http://haijia.bjxueche.net/Login.aspx?LoginOut=true',
            'Content-Type': 'application/x-www-form-urlencoded',
            'Connection' : 'Keep-Alive'
        }
        #用户名
        self.username = '62220119870513481X'
        self.password = '0513'
        self.checkCode = ''
        self.post = {
            '__VIEWSTATE':'%2FwEPDwUJLTE5MzE4NjU3D2QWAgIBD2QWAgINDxYCHglpbm5lcmh0bWwFBDM5NDdkZPCY6nrB48M%2BUmEIeDE3ea3Fz6%2F0wbg8DKRZThPQ%2F2Tm',
            '__EVENTVALIDATION':'%2FwEWBgLz8sucDwKl1bKzCQK1qbSRCwLoyMm8DwLi44eGDAKAv7D9CvcZ4oqNXIEjcECxm8KZiQP%2FA3w4BxsCXRJyGYWQxQjJ',
            'txtUserName':self.username,
            'txtPassword':self.password,
            'txtIMGCode':self.checkCode,
            'BtnLogin':'%E7%99%BB++%E5%BD%95',
            'rcode':'',
        }
        #将POST的数据进行编码转换
        self.postData = urllib.urlencode(self.post)
        #设置代理
        self.proxy = urllib2.ProxyHandler({'http':self.proxyURL})
        #设置cookie
        self.cookie = cookielib.LWPCookieJar()
        #设置cookie处理器
        self.cookieHandler = urllib2.HTTPCookieProcessor(self.cookie)
        #设置登录时用到的opener，它的open方法相当于urllib2.urlopen
        self.opener = urllib2.build_opener(self.cookieHandler,self.proxy,urllib2.HTTPHandler)

    #得到验证码图片
    def getCheckCode(self):
        self.homeUrl = "http://haijia.bjxueche.net"
        request = urllib2.Request(self.homeUrl)
        response = urllib2.urlopen(request)
        print response.read()
    def getOrderInfo(self):
        self.orderUrl = "http://haijia.bjxueche.net/ych2.aspx"
        self.orderHeaders =  {
            'Host':'haijia.bjxueche.net',
            'User-Agent' : 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36',
            'Referer' : 'http://haijia.bjxueche.net/index.aspx',
            'Content-Type': 'application/x-www-form-urlencoded',
            'Connection' : 'Keep-Alive'
        }
        filename = "cookie.txt"
        cookie = cookielib.MozillaCookieJar()
        cookie.load('cookie.txt', ignore_discard=True, ignore_expires=True)
        req = urllib2.Request(self.orderUrl,None,self.orderHeaders)
        opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
        response = opener.open(req)
        print response.read()
    def test(self):
        self.homeUrl = "http://haijia.bjxueche.net"
        filename = 'cookie.txt'
        cookie = cookielib.MozillaCookieJar(filename)
        handler = urllib2.HTTPCookieProcessor(cookie)
        opener = urllib2.build_opener(handler)
        response = opener.open("http://www.baidu.com")
        cookie.save(ignore_discard=True, ignore_expires=True)

    #程序运行主干
    def startOrder(self):
        self.getOrderInfo()

order = OrderCar()
order.startOrder()
