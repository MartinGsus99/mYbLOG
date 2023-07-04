---
title: Flask 基础
date: 2023-07-04 15:13:45
categories:
  - 后端
tags:
  - Flask
  - 笔记
  - Python
mp3:
cover: img/bg3.jpg
---

# Flask 基础

## 一、基础概念

- Web 框架，一组库和模块，使 Web 应用程序开发人员能够编写应用程序，而不必担心协议、线程管理等低级细节；
- Flask，由 Python 编写的 web 应用程序框架，基于 Werkzeug WSGI 工具包和 Jinja2 模板引擎。
- WSGI，Web Server Gateway Interface， Web 服务器网关接口，是 web 服务器和 web 应用程序之间通用接口的规范。
- Werkzeug，WSGI 工具包，实现了请求，响应对象和其他使用函数。
- Flask 环境，安装 Flask 需要 Python2.6 或者更高版本，虽然 flask 及其以来适用于 Python3，但是很多 Flask 拓展并不支持，建议在 python2.7 安装 flask

## 二、环境安装

1. 安装虚拟环境

```shell
pip install virtualenv
sudo apt-get install virtualenv
```

2. 新建文件夹，创建虚拟环境

```shell
mkdir newPro
cd newPro
virtualenv venv
venv\scripts\activate
pip install flask
pip install flask -i http://pypi.douban.com/simple/ --trusted-host pypi.douban.com
```

3. 测试

```python
from flask import Flask

# flask构造函数使用当前模块（_name_）名称作为参数
app = Flask(__name__)

#route()函数是一个装饰器，告诉应用程序那个url应该调用（rule,options)
#rule参数表示该函数的url绑定，options是要转发给基础rule对象的参数列表
@app.route('/')
def index():
    return '<h1>Hello World!</h1>'

@app.route('/user')
def getUserInfor():
    return '<h1>user page</h1>'



if __name__ == '__main__':
    app.run(host="127.0.0.1",port="3333",debug=True)
```

现代 Web 框架使用路由技术来帮助用户记住应用程序 URL。 可以直接访问所需的页面，而无需从主页导航。

## 三、基础使用

### 1. 变量规则

- string

- int

- float

- path：接受用作目录分隔符的斜杠

  ```python

  @app.route('/user/<int:id>')
  def getUserID(id):
      return '<h1>Hello,%d!</h1>'%id

  @app.route('/user/<float:id>')
  def getUserID2(id):
      return '<h1>Hello,%f!</h1>'%id

  @app.route('/user/<path:id>')
  def getUserID3(id):
      return '<h1>Hello,%s!</h1>'%id
  ```

### 2. URL 构建

**url_for（）**函数对于动态构建特定函数的 URL 非常有用。 该函数接受函数的名称作为第一个参数，以及一个或多个关键字参数，每个参数对应于 URL 的可变部分

```python

@app.route('/show_blog/<int:postID>')
def show_blog(postID):
    return '<h1>blog number is %d</h1>'%postID

@app.route('/blog/<int:postID>')
def show_blog_admin(postID):
    if postID==0:
      return redirect(url_for('show_blog',postID=1))
    else:
      return redirect(url_for('show_blog',postID=postID))

```

### 3. Http 方法

在此协议中，定义了从指定的 URL 检索不同的数据方法

- GET：不加密发送数据到服务器
- HEAD：和 GET 一样，没有响应体（？）
- POST：用于将 HTML 表单数据发送到服务器，POST 方法接收的数据不由服务器缓存
- PUT：用所上传的内容替换目标资源的所有当前表示
- DELETE：删除由 URL 给定的目标资源的所有当前表示

```py
from flask import Flask,redirect,url_for,render_template,request,session,flash

app=Flask(__name__)

@app.route('/success/<name>')
def success(name):
  return 'welcome %s'%name

@app.route('/login',methods=['POST','GET'])
def login():
  if request.method=='POST':
    user=request.form['nm']
    return redirect(url_for('success',name='POST:'+user))
  else:
    user=request.args.get('nm')
    return redirect(url_for('success',name='GET:'+user))

if __name__=='__main__':
  app.run(debug=True)
```

- 服务器通过 post 方法接收数据，从表单数据获得的“nm”参数的值通过

```py
user=request.form['nm']
```

- 服务器通过 get 方法接收数据，从表单数据获得的“nm”参数通过

```py
User=request.args.get('nm')
```

### 4.模板

可以以 HTML 的形式返回绑定到某个 URL 的函数输出

```python
@app.route('/')
def index():
   return '<html><body><h1>Hello World'</h1></body></html>'

```

从 python 代码返回 HTML 很麻烦，可以利用基于 Flask 的 Jinja2 模板引擎，通过`render_template()`函数呈现 HTML 文件

```python
@app.route('/')
def index():
    return render_template('login.html')
```

Flask 将尝试在 templates 文件夹中找到与此脚本所在的文件夹中的 HTML 文件。

Jinja2 使用一下定界符从 HTML 转义：

- {% ... %} for statements

- {{ ... }} for expression to print to the template output
- {# ... #} for comments not included in the template output

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>

  <body>
    <h1>Welcome,{{ name }}</h1>
    {% if age > 20 %}
    <h2>You are very nice~</h2>
    {% else %}
    <h2>You are very young~</h2>
    {% endif %}
  </body>
</html>
```

### 5. 静态文件

网络应用程序通常需要一个静态文件，例如支持显示网页的 js 文件或者 css 文件；

通常，网络服务器配置服务，但是在开发过程中，这些文件从 static 文件夹或者模块旁提供；

```html
<script
  type="text/javascript"
  src="{{ url_for('static', filename = 'index.js') }}"
></script>
```

### 6. Flask 请求对象

来自客户端网页得数据作为全局请求对象发送到服务器。

- 表单：字典对象，包含表单参数键值对
- args：在问号后面得 url 得一部分查询字符串得解析内容
- cookie:保存 cookie 名称和值得字典对象
- 文件：与上传文件相关得数据
- 方法：当前请求方法

### 7. 将表单数据发送到模板

```

```
