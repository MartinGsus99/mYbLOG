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

{.% ... %.} for statements
{.{ ... }.} for expression to print to the template output
{# ... #} for comments not included in the template output

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

```py
from flask import Flask,request,render_template

app = Flask(__name__)

@app.route('/')
def student():
    return render_template('student.html')
  
@app.route('/result',methods = ['POST', 'GET'])
def result():
    if request.method == 'POST':
        result = request.form
        return render_template("result.html",result = result)
      
if __name__ == '__main__':
  app.run(debug = True)
```

```html
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>

<body>
  <form action="http://127.0.0.1:5000/result" method="POST">
    <label for="name">Name:</label>
    <input type="text" id="name" name="name"><br><br>
    <label for="age">Age:</label>
    <input type="text" id="age" name="age"><br><br>
    <label for="job">Job:</label>
    <input type="text" id="job" name="job"><br><br>
    <input type="submit" value="Submit">
  </form>
</body>

</html>
```

```html
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>

<body>
  <table>
    {% for key, value in result.items() %}
    <tr>
      <th> {{ key }} </th>
      <td> {{ value }}</td>
    </tr>
    {% endfor %}
  </table>
</body>

</html>
```

### 8.Flask Cookies

Cookie以文本形式存储在客户端的计算机上，目的是记住与客户使用相关的数据，以获得更好的访问者体验和网站统计信息；

Request对象包含cookie得属性，它是所有得cookie变量及其对应值得字典对象。

Flask中处理Cookie得步骤为：

1. 设置cookie

```py
resp=make_response("success")
resp.set_cookie("martin","martin",max_age=3600)
```

2. 获取cookie

```py
cookie=request.cookies.get("martin")
```

3. 删除cookie（让cookie过期）

```py
resp=make_response("del martin")
resp.delete_cookie("martin")
```

### 9. Flask Session

Session数据存储在服务器。事客户端登录到服务器并注销服务器的时间间隔。需要在该会话中保存的数据会存储到服务器上的临时目录中。

为每个客户端得会话分配会话ID，会话数据存储在cookie得顶部，服务器以加密方式对其签名。

Session对象也是一个字典对象，包括会话变量和关联值得键值对；

```py
from flask import Flask,request,session,redirect,url_for,flash
from flask import abort,make_response
from flask import render_template

app=Flask(__name__)

app.secret_key='990526'


@app.route('/')
def index():
    if 'username' in session:
        username=session['username']
        return 'Logged in as '+username+'<br>'+\
            "<b><a href='/logout'>click here to log out</a></b>"
    return "You are not logged in <br><a href='/login'></b>"+\
        "click here to log in</b></a>"

@app.route('/login',methods=['GET','POST'])
def login():
    if request.method=='POST':
        session['username']=request.form['username']
        return redirect(url_for('index'))
    return '''
        <form action="" method="post">
            <p><input type=text name=username>
            <p><input type=submit value=Login>
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('username',None)
    return redirect(url_for('index'))
  
if __name__=='__main__':
    app.run(debug=True)
```

### 10. Flask重定向和错误

> Flask类有一个redirect（）函数，调用时，返回一个响应对象，并将用户重定向到具有指定状态代码的另一个目标位置。

```py
Flask.redirect(location,statuscode,response)
```

- location:重定向响应得url
- statuscode：发送到浏览器标头，默认302
- response：用于实例化响应

> Flask类具有带有错误代码的abort()函数

```py
Flask.abort(code)
```

Code为以下之一：

- 400 错误请求
- 401 未进行身份认证
- 403 Forbidden
- 404 未找打
- 406 不接收
- 415 不支持的媒体类型
- 429 请求过多

```py
@app.route('/login',methods = ['POST', 'GET'])
def login():
   if request.method == 'POST':
      if request.form['username'] == 'admin' :
         return redirect(url_for('success'))
      else:
         abort(401)
   else:
      return redirect(url_for('index'))
```

### 11.Flask消息闪现

Flask提供了一个非常简单得方法来使用闪现系统向用户反馈信息。

在一个请求结束时记录一个信息，并且在下次请求时访问它，通常与布局模板结合以公开信息。

Flask框架得闪现系统可以在一个视图中创建消息，并在名为next得试图函数中呈现他。

Flask模块包含flash（）方法，将消息传递给下一个请求，请求通常为模板；

```
flash(message,category)
```

- message:闪现的实际消息
- category：error | info | warning

从会话中删除消息，模板调用get_flashed_messages()

### 12.Flask Sqlite

Flask中使用特殊得g对象可以使用before_request()和teardown_request()在请求开始前打开数据库连接，请求结束之后关闭连接；

```py
import sqlite3
from flask import g,Flask

DATABASE='../database.db'

app=Flask(__name__)

def connect_db():
    return sqlite3.connect(DATABASE)

@app.before_request
def before_request():
    g.db=connect_db()
  
@app.teardown_request
def teardown_request(exception):
    if hasattr(g,'db'):
        g.db.close()
```

#### 按需连接

上述方式在Flask执行请求前处理器才有效。如果在脚本或者Python解释器中，必须使用：

```py
with app.test_request_context():
	app.preprocess_request()
```

#### 简化查询

```py
for user in query_db("select * from users")
	print user['username'],'has the id',user['user_id']
```

只需要单一结果的用法：

```py
user=query_db('select * from users where username=?',[the_username],one=true)

if user is None:
    	print 'No such user'
    else:
        print the_username,'has the id',user['user_id']
```

如果要给 SQL 语句传递参数，请在语句中使用问号来代替参数，并把参数放在一个列表中 一起传递。不要用字符串格式化的方式直接把参数加入 SQL 语句中，这样会给应用带来 [SQL 注入](http://en.wikipedia.org/wiki/SQL_injection) 的风险。

### 13. Flask文件上传

Flask中处理文件上传非常简单，需要一个HTML表单，其enctype属性设置为`multipart/form-data`，将文件发布到URL

URL处理程序从`request.files[]`对象提取文件，保存到所需位置；

上传的文件首先保存到服务器上的临时位置，然后实际保存到最终位置；

```
app.config['UPLOAD_FOLDER']定义文件上传文件夹的位置
```

```
app.config['MAX_CONTENT_LENGTH']指懂要上传文件的最大大小（字节）
```

> py文件不嫩放到views文件下

### 14.Flask部署

开发服务器上的APP只能在设置了开发环境的计算机上访问，这是一种默认i行为，因为在调试模式下，用户可以在计算机上执行任意代码。

如果禁用了debug，则可以将主机名设置为‘0.0.0.0’，使本地计算机上得开发服务器可供网络上的用户使用。

```
app.run(host='0.0.0.0')
```

#### 部署

要从开发环境切换到成熟得生产环境，需要在真是得web服务器上部署应用程序

#### mod_wsgi

是一个Apache模块，它提供了一个WSGI兼容接口，用于在Apache服务器上托管基于Python得web应用程序。

```
pip install mod_wsgi
mod_wsgi-express start-server
```

### 15. Flask FaskCGI

FastCGi是Nginx,Lighttpd和Cherokee等服务器上的Flask应用程序













