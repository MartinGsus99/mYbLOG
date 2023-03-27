---
title: Web开发安全
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - 网络安全
    - 笔记
mp3: 
cover: img/bg1.jpg
---



# Web开发安全

# 攻击篇

## 一、Cross-site Scripting(XSS)跨站脚本攻击

### 1.主要利用点

- 盲目信任用户的提交内容；
- string->Dom

```js
doucument.write
element.innerHTML=anyString
SSR(user_data)	//伪代码
```

### 2.特点

- 很难从UI感知；
- 窃取用户信息（Cookie/token）；
- 绘制UI（例如弹窗），诱骗用户点击/填写表单；

![](https://s3.bmp.ovh/imgs/2023/02/06/bab761782d523687.jpg)

### 3.类别

- stored XSS（存储型xss）

```
-恶意脚本被存储在数据库中
-访问页面->读数据->被攻击
-危害最大，对全部用户可见
```

- reflected XSS (反射型xss)

```
-不涉及数据库
-从URL攻击
```

![](https://s3.bmp.ovh/imgs/2023/02/06/01aa21181b743218.jpg)

- DOM-based XSS

```
-不需要服务器参与
-恶意攻击的发起+执行，全部在浏览器完成
```

![](https://s3.bmp.ovh/imgs/2023/02/06/8f74704368f2a414.jpg)

![](https://s3.bmp.ovh/imgs/2023/02/06/83dda8008e3c1b19.jpg)

- Mutation-based XSS 

```
-利用浏览器渲染DOM的特性（独特优化）
-不同的浏览器，会有区别（按照浏览器进行攻击）
```

![](https://s3.bmp.ovh/imgs/2023/02/06/2db16e9e30d05689.jpg)

Note：其实就是闭合双引号；

## 二、Cross-site request forgery(CSRF)跨站伪造请求

### 1.特点

- 在用户不知情的前提下
- 利用用户权限Cookie
- 构造指定HTTP请求，窃取或者修改用户敏感信息

![](https://s3.bmp.ovh/imgs/2023/02/06/1cb69b1cdfc1f80f.jpg)

### 2.Get请求

![](https://s3.bmp.ovh/imgs/2023/02/06/315569b1ad5267c7.jpg)

## 三、注入

### 1.SQL Injection

![](https://s3.bmp.ovh/imgs/2023/02/06/bdfe27a1758bff45.jpg)

![](https://s3.bmp.ovh/imgs/2023/02/06/d8d8412ddb795269.png) 

### 2.更多注入

- CLI
- OS command
- Server-side Request Forgery(SSRF),服务端伪造请求；严格来说并不是注入，但是原理类似；

![](https://s3.bmp.ovh/imgs/2023/02/06/c853331fa801b755.jpg)

##### 读取+修改

![](https://s3.bmp.ovh/imgs/2023/02/06/d326f66d918f6e14.jpg)

SSRF Demo

![](https://s3.bmp.ovh/imgs/2023/02/06/730fd31cf9f769ca.jpg)

## 四、DOS

> 通过某种方式（构造特定请求），导致服务器资源被消耗殆尽，来不及响应更多请求，导致请求被挤压，进而形成雪崩效应；

### 1.正则表达式------贪婪模式

```js
const greedyRegExp=/a+/;
const noGreedyRegExp=/a+?/;
const str='aaaaaaa';

result1=str.match(greedyRegExp)[0];			// "aaaaaaa"
result2=str.match(noGreedyRegExp)[0];		// "a"

```

### 2.ReDOS 基于正则表达式的DoS

![](https://s3.bmp.ovh/imgs/2023/02/06/c28283945d9c0451.jpg)

### 3.DDos

> 短时间内，来自大量僵尸设备的请求流量，服务器不能及时完成全部请求，导致请求堆积；

##### Logical DOS

- 耗时的同步操作
- 数据库写入
- SQL join
- 文件备份
- 循环执行逻辑

![](https://s3.bmp.ovh/imgs/2023/02/06/bade294c53a9fd51.jpg)

## 五、中间人攻击

![](https://pic.imgdb.cn/item/63e069224757feff33a5d839.jpg)

# 防御篇

## 一、XSS

### 1.防御方法

##### 原则

- 永远不要相信用户的提交内容
- 永远不要将用户提交的内容转换为DOM

##### 前端

- 主流框架默认防御XSS
- googole-closure-library

##### 服务端（Node）

- DOMPurify

##### 业务需要用户生成DOM

- 需要对string进行转义
- 上传的svg文件需要进行扫描
- Blob动态生成script
- 自定义样式（自定义背景图片，url）

### 2.同源策略

- 协议、域名、端口号完全相同；

### 3.CSP（content security policy）

- 那些源认为是安全的
- 对来自安全源的脚本可以执行，否则直接抛错
- 对eval+inline script 说No！！！！

![](https://pic.imgdb.cn/item/63e06b684757feff33a91d70.jpg)

## 二、CSRF

![](https://pic.imgdb.cn/item/63e06ba14757feff33a96e53.jpg)

##### token

![](https://pic.imgdb.cn/item/63e06bed4757feff33a9e138.jpg)

##### iFrame攻击

![](https://pic.imgdb.cn/item/63e06cac4757feff33aaec65.jpg)

> button是none的，所以点击button下穿到了底下的iframe页面；

##### anti-pattern

```js
//GET!==GET+POST
//将更新+获取放到同一个GET接口；
pulic async getAndUpdate(ctx){
    const{update,id}=ctx.query;
    if(update){
        await this.update(update);
    }
    ctx.body=await this.get(id);
}
```

##### 避免用户信息被携带：same site cookie

![](https://pic.imgdb.cn/item/63e06e0e4757feff33ad8660.jpg)

![](https://pic.imgdb.cn/item/63e06e224757feff33adb6f3.jpg)

##### 问题：第三方服务依赖于cookie怎么办？

```
Set-Cookie:SameSite=None;Secure;
```

![](https://pic.imgdb.cn/item/63e06eb34757feff33aec45d.jpg)

## 三、Injection

- 找到查询SQL的地方
- 使用prapared statement
- 最小权限原则：禁止sudo || root
- 建立允许名单+过滤：禁止rm
- 对URL类型参数进行协议、域名、ip等限制：禁止访问内网

## 四、DOS

### 1.RegexDos

- code review
- code scan+正则性能测试
- 禁止使用用户提供的正则

### 2.DDoS

- 流量治理：负载均衡、API网关、CDN （过滤）
- 快速自动扩容        (抗量)
- 非核心服务降级  （抗量）

### 3.中间人

![](https://pic.imgdb.cn/item/63e070324757feff33b1206f.jpg)

- 可靠：加密
- 完整：MAC校验
- 不可抵赖：数字签名

### 4.SRI  子资源集成

静态资源被劫持篡改？

对比Hash !!!

![](https://pic.imgdb.cn/item/63e071574757feff33b2d91a.jpg)







