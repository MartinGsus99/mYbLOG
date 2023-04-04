---
title: Ajax
date: 2021-04-12 23:41:10
categories: 
    - 前端
tags: 
    - 面试
    - 笔记
mp3: 
cover: img/bg1.jpg
---

# AJAX

```
Asynchronous Javascript and XML;(异步的javascript和XML)。
```

✨无须更新整个网页的情况下，更新部分网页；

传统的网页，需要更新或者提交一个表单，都需要重新加载整个网页；

增强了B/S（浏览器/服务器）的体验性；

高可用，更丰富，更动态；

#### Ajax的核心：XHR(XMLHttpRequest),能够以异步方式从服务器获取新数据；用于在后台与服务器交换数据。这意味着可以在不重新加载整个网页的情况下，对网页的某部分进行更新。

```js
variable=new XMLHttpRequest();
```

1.发送请求open和send方法

```javascript
xmlhttp.open("GET","test1.txt",true);
xmlhttp.send();
```

| 方法                       | 描述                                                         |
| -------------------------- | ------------------------------------------------------------ |
| open（method，url，async） | method：GET POST；url:文件在服务器的位置；async：true同步，false异步； |
| send（string）             | 将请求发送到服务器：string：仅适用于POST                     |

2.GET 还是 POST？

与 POST 相比，GET 更简单也更快，并且在大部分情况下都能用。

然而，在以下情况中，请使用 POST 请求：

- 无法使用缓存文件（更新服务器上的文件或数据库）
- 向服务器发送大量数据（POST 没有数据量限制）
- 发送包含未知字符的用户输入时，POST 比 GET 更稳定也更可靠

3.通过 AJAX，JavaScript 无需等待服务器的响应，而是：

- 在等待服务器响应时执行其他脚本
- 当响应就绪后对响应进行处理

