---
title: Session And Cookie
date: 2023-04-06 19:51:45
categories: 
    - 前端
tags: 
    - session
    - cookie
mp3: 
cover: img/bg10.jpg
---


# Session And Cookie

## 一、Session和Cookie简介

### 1.简介

> Cookie的出现是因为http是无状态协议，服务器记不住访问者，刷新一次页面可能就需要输入账号密码重新登录；
>
> cookie作用就是让服务器认识你；

- cookie可以认为是一个变量，形如name=value,存储在浏览器；
- 一个session可以理解为一个数据结构，多数情况是`映射`，存储在服务器上；

> cookie可以在服务器通过http的SetCookie字段设置Cookie；

```go
func cookie(w http.ResponseWriter, r *http.Request){
    http.SetCookie(w,&http.Cookie){
        Name:'Martin',
        Value:'128'
    }
    
      http.SetCookie(w,&http.Cookie){
        Name:'Jacy',
        Value:'129'
    }
}
```

> 当浏览器访问对应网址时，通过浏览器的开发者工具查看此次HTTP通信的喜姐，可以看见服务器的回应发出来两次SetCookie命令；
>
> 此后，浏览器请求中的Cookie都会带上这两个字段；

### 2. cookie的问题

cookie字段存储在HTTP Header中，如果cookie的信息越来越多，会消耗更多的带宽；

### 3. session + cookie

- 一个cookie存储一个变量 sessionID='123456';
- 仅仅将一个cookie传递给服务器，服务器通过ID查询对应的session，这个session是一个数据结构，存储了各种用户的信息，有效解决了追踪用户的问题。
- session是一个数据结构，由网站的开发者设计，可以承载各种数据；
- 由于存储在服务器，所以session会有过期时间，一般是定期删除过期的session；

## 二、Session的实现

### 1.实现

- Manager
- Provider
- Session

![](https://s3.bmp.ovh/imgs/2023/04/06/d80d75f3d72fd150.png)

1. 浏览器通过HTTP协议向服务器请求资源，对应路径上有个Handler函数接受请求，解析HTTPheader中的cookie，得到SessionID，发送给Manager；
2. Manager充当session管理器的角色，主要存储一些配置信息，比如session存活时间，cookie的名字等；所有的session存在Manager内部的Provider中，Manager会把sessionID传递给Provider；
3. Provider是一个容器，散列表，将sessionID和session一一对应，收到Manager的sid后，查询session并返回；
4. Handler根据session中的信息，进行处理，返回对应的HTML信息；

### 2.为什么要划分Manager、Provider、Session

- session结构可能不止一个哈希表，还存储辅助数据等；
- session可能有不同的存储方式：比如村粗缓存数据库redis或者存入Mysql；因此session结构提供一层抽象，屏蔽不同存储方式的差异；
- Provider内部会很复杂，需要适应不同的算法比如LRU缓存淘汰算法，来存储session；
-  Manager 主要就是⼀个参数集合，⽐如 session 的存活时间，清理过期 session 的策略，以及 session 的可⽤存储⽅式。 Manager 屏蔽了操作的具体 细节，我们可以通过 Manager 灵活地配置 session 机制。













