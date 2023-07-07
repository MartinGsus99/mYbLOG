---
title: Nginx
date: 2023-07-06 08:51:45
categories:
  - Nginx
tags:
  - Nginx
mp3:
cover: img/bg13.jpg
---

# Nginx

## 一、简介

- Web 服务器
- 解决 C10K 问题
- 最大 5w 个并发连接

## 二、基本使用

### 1.基础

```shell
#启动
nginx

ps -ef | grep nginx

#查看端口占用
lsof -i:80

#优雅停止
nginx -s quit
#立即停止
nginx -s stop

#重载配置文件
reoad

#重新打开日志文件
reopen

#查看配置文件位置
nginx -t
```

master 进程：负责读取和验证配置文件，管理 woker 进程，一个

worker 进程：负责处理实际请求，多个

![](https://s3.bmp.ovh/imgs/2023/07/06/0fd07985cc88f932.png)

### 2.静态网站

HEXO 搭建博客，略

### 3.配置文件

```json
#核心数，和cpu数目一致最好
work-processes 10

#每个核心能够连接的网络连接
events{
    work_connections 1024;
}

http{
    include mime.types   //包含相应的文件处理方法

    server{

	}

	server{

    }

	include servers/*   //保存单个server配置文件
}

```

### 4.反向代理和负载均衡

- 正向代理：代理客户端
- 反向代理：代理服务端

多个服务器对一个域名，隐藏服务器真实 IP

```js
upstream backend{
	//需要代理的服务器
    ip_hash;     //统一浏览器hash到一个服务器，以后一直都是访问这个服务器了
	server 127.0.0.1:8001 weight=3;
	server 127.0.0.1:8002 weight=1;
	server 127.0.0.1:8003 weight=1;
}

server{
    location /app{
        proxy_pass http://backend;
    }
}
//默认轮询访问三个服务器
```

### 5.Https
