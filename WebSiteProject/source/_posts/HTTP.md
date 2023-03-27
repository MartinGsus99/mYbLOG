---
title:  HTTPS实用指南
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - 计算机网络
    - 笔记
mp3: 
cover: img/bg6.jpeg
---


# HTTPS实用指南

## 一、初识

### 1.背景知识

输入网址获得网页的过程？

![](https://s3.bmp.ovh/imgs/2023/02/03/f6ce5b862569e192.jpg)

##### HTTP发展

![](https://s3.bmp.ovh/imgs/2023/02/03/bd303c5375ece729.jpg)

### 2.报文内容

![](https://s3.bmp.ovh/imgs/2023/02/03/eb7f13f8f1a5596c.jpg)

```
常用请求头
```

![](https://s3.bmp.ovh/imgs/2023/02/03/1848c837bc2cf08d.jpg)

```
常用响应头
```

![](https://s3.bmp.ovh/imgs/2023/02/03/08fd49af7f73a5af.jpg)

### 3. Methods

![](https://s3.bmp.ovh/imgs/2023/02/03/83884b861c15d41f.jpg)

- 安全的（不会修改服务器数据）：GET HEAD OPTIONS
- 幂等（同样的请求执行一次和多次的效果是一致的）：所有安全的方法都是幂等的+PUT DELETE；

### 4.状态码

![](https://s3.bmp.ovh/imgs/2023/02/03/86f6032a7181310d.jpg)

### 5. Restful API

- 每一种URL代表一种资源；
- 客户端和服务器之间，传递这种资源的某种表现层；
- 客户端通过HTTP Methods,对服务端资源进行操作，实现“表现层状态转化”；

![](https://s3.bmp.ovh/imgs/2023/02/03/377079155bbec1bc.jpg)

### 6.缓存

![](https://s3.bmp.ovh/imgs/2023/02/03/65a645bc76884d65.jpg)

- 强缓存资源本地有就直接用本地资源
- 协商缓存即使本地有缓存，但是还是需要和server端进行通信确认是否最新等；

```
缓存流程示意
```

![](https://s3.bmp.ovh/imgs/2023/02/03/1bd6b0f0379d4254.jpg)

### 7. Cookie

![](https://s3.bmp.ovh/imgs/2023/02/03/f2c87718dc00674c.jpg)

### 8. HTTP/2

> 更快、更稳定、更简单

- 使用帧作为通信的最小单位，每个帧都包含头，至少回标识出当前帧所属的数据流；
- 采用二进制编码，效率更高，有更好的压缩算法；
- 消息：与逻辑请求或者响应消息对应的完整的一系列帧；
- 数据流：已建立的连接内双向字节流，可以承载一条或多条消息；
- 交错发送，接收方重组织；
- 链接都是永久的，而且仅需要每个来源一个连接；
- 流控制：阻止发送方向接收方发送大量数据的机制（似乎可以防范DDOS？）

![](https://s3.bmp.ovh/imgs/2023/02/03/e85b4b47fe56a57a.jpg)

### 9.  HTTPS

```
经过TSL/SSL加密
```

![](https://s3.bmp.ovh/imgs/2023/02/03/d6e3190e2ebe64b2.jpg)

## 二、HTTP协议的应用场景分析

### 1.静态资源

```
方案：缓存+CDN+文件名Hash
```

- CDN (Content Delivery Network) :通过用户就近性和服务器负载进行判断，提供快速服务；CDN复杂解决文件加载快慢；
- 文件名Hash来保证每次刷新获得的资源是最新的；

### 2.登录

头条页面密码登录会发出两个请求；

- 请求1的Methods是OPTIONS：跨域、cross-origin

```
一个url由scheme+host name+port组成
e.g. https://www.example.com:443
跨域：scheme、host name、prot任意一个有区别都认为是跨域；
Note：如果https没有写明443端口号也可以认为是同域；http默认80；port可以不写；
```

- 跨域

![](https://pic.imgdb.cn/item/63dc762107d5ca72062d5196.jpg)

##### 跨域解决方案：

- CORS
- 代理服务器：同源策略是浏览器的安全策略，不是http的

![](https://s3.bmp.ovh/imgs/2023/02/03/2ed3f548ffca14ab.jpg)

- IFrame：存在诸多不便；

![](https://pic.imgdb.cn/item/63dc76b007d5ca72062e430c.jpg)

##### 鉴权

- session+cookie
- JWT（JSON web token）token具有唯一性；

![](https://pic.imgdb.cn/item/63dc76fe07d5ca72062e9fdb.jpg)

- SSO（Single Sign On）：单点登录

重定向到子站就进行登录态查询，登陆在线则可以继续访问；不在线跳转到SSO登录后继续访问；

## 三、实战

### 1. Ajax之XHR

### 2.常用请求库Axios（参考官网）

### 3.网络优化（需要补充）

![](https://pic.imgdb.cn/item/63dc79d407d5ca7206341e84.jpg)

### 4.稳定性

- 重试是保证稳定性的有效手段，但是要防止滥用，导致server情况更加恶劣；
- 缓存合理使用，作为最后一道防线；

![](https://pic.imgdb.cn/item/63dc7a1507d5ca7206351481.jpg)

## 四、拓展

### 1.Websocket

- 进行全双工的通讯；
- 实时性要求较高，例如聊天室；（开启聊天室demo）
- url使用ws:// 或者 wss：//

### 2.QUIC（Quick UDP Internet Connection）

- 相比于TCP更快；
- 可靠性类似于TCP；
- 支持h2的多路复用，没有TCP的HOL文通；
- 前向纠错FEC
- 用户空间的阻塞算法，最新的BBR算法；







