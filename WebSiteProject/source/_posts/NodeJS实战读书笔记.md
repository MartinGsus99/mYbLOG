---
title:  NoDe JS 实战
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - Node
    - 笔记
mp3: 
cover: img/bg25.jpg
---


# NoDe JS 实战

## 一、Welcome to node

### 1.NodeJS基础

- 显著特征：异步、事件驱动机制
- Node和JS的优势之一是单线程编程。为了实现同步，引入事件机制，点击按钮，触发事件，规避资源死锁和竞态条件
- 非阻塞I/O

> 程序可以在做其他事情的时候发起一个请求来获取网络资源，然后网络操作完成之后，运行一个回调函数来处理操作的结果

- Node与V8

> Node的动力源自V8引擎。V8的特性之一是会将JS代码直接编译为机器码。

- 特性组

  > Node包含了v8提供的ES6特性，分为shipping、staged、in progress三组；
  >
  > 其中shipping是默认开启的，staged和in progress需要命令行参数开启

  ```shell
  node --harmony
  node --v8-options | grep "in progress"
  ```

- npm

  >  npm要求Node项目目录下有一个package.json文件；

  ```shell
  npm init -y    //初始化package.json
  ```

- 核心模块

> fs，path，net，http/s，dns，assert，os

```js

//调取文件流
const fs=require('fs');
const zlib=require('zlib');
const gzip=zlib.createGzip();
const outStream=fs.createWriteStream('output.js.gz');

fs.createReadStream('./fs.js').pipe(gzip).pipe(outStream);
```

```js
//网络模块
const http=require('http');
const port=8080;

const server=http.createServer((req,res)=>{
    res.end("HEllo,node js!");
});

server.listen(port,()=>{
    console.log("Server listening on:http://localhost:%s",port);
});
```

```shell
//调试器
node debug server.js
```

- 主流Node程序：Web、命令行工具、桌面程序 

> Node可以将TS转换为JS；

## 二、Node编程基础

- 如何组织代码？
- 如何实现异步编程？

### 1.Node功能的组织及重用

![](https://s3.bmp.ovh/imgs/2023/02/05/b3bf8ebded4c5d97.jpg)

> 上面的做法会出现一个问题，就是两个文件声明了相同的变量名，导致重复声明；
>
> PHP和Ruby等语言使用命名空间来解决问题；
>
> Node选择不给程序员污染全局命名空间的机会；
>
> Node模块允许从被引入文件中选择要暴露给程序的函数和变量，如果模块返回的函数或者变量不止一个，那么可以通过设定exports对象的属性来指明他们。

![](https://s3.bmp.ovh/imgs/2023/02/05/40f820b01ac722a9.jpg)

### 2.创建一个Node项目

```shell
mkdir myApp
cd myApp
npm init -y   //全部使用默认值的package
```

> require是Node中少数几个同步I/O操作之一；
>
> I/O密集的地方尽量不要使用require，所有的同步调用都会阻塞Node；

### 3. node_modules重用模块

> 要求模块在文件系统中使用相对路径存放，对于组织程序特定的代码很有帮助。但是对于想要在程序见共享或者跟他人共享代码却用处不大。
>
> Node有一个独特的模块引入机制，即node_modules,其模块检索规则如下：

![](https://s3.bmp.ovh/imgs/2023/02/07/4accd465166d6500.jpg)

##### 注意事项：

- 如果模块是目录，在模块目录中定义模块的文件必须命名为index.js。除非在这个目录下一个叫package.json的文件特别执行。要执行一个取代index.js的文件，必须使用JSON数据定义的对象；

```json
{
    "main":"currency.js"
}
```

![](https://s3.bmp.ovh/imgs/2023/02/07/eb62dc14f1e8a0e5.jpg)

- Node能把模块作为对象缓存起来。如果两个文件引入了相同的模块，第一个require会把模块返回的数据存到内存中。第二个引入会从内存中加载。

![](https://s3.bmp.ovh/imgs/2023/02/07/3baf64653ff8e710.jpg)

##### ！！！！！！不能实现

### 4.异步编程

Node世界的两种响应逻辑方式：

- 回调：通常用来定义一次性响应的逻辑。比如数据库查询；
- 事件监听：本质上也是一个回调，不同的是和一个概念实体有关（事件）；

```js
//下面的例子中，用EventEmitter.Prototype.on方法在服务器上绑定了一个监听器，当有request事件发出，服务器调用handleRequest函数

server.on('request',handleRequest);
```

Node Http服务器实例是一个事件发射器，一个可以类（Event Emitter）；

Node的很多核心功能都继承自EventEmitter；

##### 用回调处理一次性事件

> 回调是一个函数，被当作参数传递给异步函数，用来描述异步操作完成之后要做什么。

实例如下：

- 异步获取存放在json文件中的文章标题
- 异步获取简单的HTML模板
- 将标题组装到HTML页面里
- 将HTML发送给客户

```js
const http=require('http');
const fs=require('fs');

http.createServer((req,res)=>{
    getTitles(res);
}).listen(8000,'127.0.0.1');

//将回调嵌套的功能代码提取出来
function getTitles(res){
    fs.readFile('./data/title.json',(err,data)=>{
        if(err) return hadError(err,res);
        getTemplate(JSON.parse(data.toString()),res);
    });
}

function getTemplate(titles,res){
    fs.readFile('./index.html',(err,data)=>{
        if(err) return hadError(err,res);
        formatHtml(titles,data.toString(),res);
    })
}

function formatHtml(titles,templ,res){
    const html=templ.replace('%',titles.join('</li><li>'));
    res.writeHead(200,{'Content-Type':'text/html'});
    res.end(html);
}

function hadError(err,res){
    console.log(err);
    res.end("Server Error");
}
```

##### 用事件发射器处理重复性事件

> 事件发射器会触发事件，并且在那些事件被触发时能处理他们；
>
> 重要的Node API组件，比如HTTP服务器、TCP服务器和流都被做成了事件发射器；

```js
socket.on('data',handleData)
```

echo服务器的例子：

```js
const net=require('net');
const server=net.createServer(socket=>{
    socket.on('data',data=>{
        socket.write("Your message is: "+data+".\n");
    });
    //只响应一次
    socket.once('data',data=>{
        socket.write("Your message is: "+data+".\n");
    });
});

server.listen(8000,'127.0.0.1');
```

```shell
telnet 127.0.0.1 8888
```

##### 一个PUB/SUB的例子

下面的代码定义了channel事件发射器，并带有一个监听器，可以监听channel中发生的事件并做出响应；

```js
//定义
const EventEmitter=require('events').EventEmitter;
const channel=new EventEmitter();
channel.on('join',()=>{
    console.log("Welcome!");
})

//触发事件/发射事件/join是事件名称，可以为任何值
channel.emit('join');
```

完整实现代码如下（存在只能输出一个字符的问题，似乎需要上缓存）：

```js
const events=require('events');
const net=require('net');
const channel=new events.EventEmitter();
var fullMessage="";

channel.clients={};
channel.subscriptions={};

channel.on('join',function(id,client){
    this.clients[id]=client;
    const welcomeMessage=`Welcome! ${this.listeners('broadcase').length+1} guests online!`;
    client.write(`${welcomeMessage}\n`);
    this.subscriptions[id]=(senderId,message)=>{
        if(id!=senderId){
            this.clients[id].write("Message from user "+id+":"+message+".\n");
        }
    };
    this.on('broadcase',this.subscriptions[id]);
    console.log(`${id} has enter the chatroom.\n`);
    channel.emit('boradcast',id,`${id} has enter the chatroom.\n`);
});

//绑定leave事件；
channel.on('leave',function(id){
    channel.removeListener('broadcast',this.subscriptions[id]);
    console.log(`${id} has left the chatroom.\n`);
    channel.emit('boradcast',id,`${id} has left the chatroom.\n`);
});

//绑定lshuwdown事件,提出所有用户；
channel.on('shutdown',function(id){
    channel.emit('broadcast','','The server has shut down.\n');
    console.log(`${id} has close the chatroom.\n`);
    channel.removeAllListeners('broadcast');
});

//设定监听器最多的数量为50；
channel.setMaxListeners(50);

const server=net.createServer(client=>{
    const id=`[${client.remoteAddress}:${client.remotePort}]`;
    channel.emit('join',id,client);
    client.on('data',data=>{
        data=data.toString();
        if(data==='*'){
            channel.emit('shutdown',id);
        }
        if(data==='-'){
            channel.emit('leave',id);
        }
        channel.emit('broadcase',id,data);
    });
    client.on('close',()=>{
        channel.emit('leave',id);
    });
});

server.listen(8888);
```

### 5.异步开发的难题

> 创建异步程序时，需要关注：
>
> 1.事件轮询的条件；
>
> 2.程序变量；
>
> 3.其他随程序逻辑执行而发生变化的资源；

```js
//作用域是如何导致bug出现的

function  asyncFunction(callback){
    setTimeout(callback,200);
}

let color='green';				//初始color
asyncFunction(()=>{
    console.log(`The color is ${color}.`);			//等待200ms输出color
});

color='blue'			//结果为输出blue；
```

> JS闭包可以冻结color的值；
>
> 下面的例子对asyncFunction的调用被封装到一个以color为参数的匿名函数里。

```js
color='blue'			
(color=>{
    asyncFunction(()=>{
        console.log(`The color is `,color);
    });
})(color);

color='green';				//结果为输出blue；
```

### 6.异步逻辑的顺序化

> 让一组异步任务顺序执行的概念被Node社区称为流程控制；
>
> 控制分为：串行、并行

![](https://s3.bmp.ovh/imgs/2023/02/09/b33ca1d4d596f929.jpg)

#### （1）串行流程控制

```js
//以下代码用回调让任务顺序执行
setTimeout(()=>{
    console.log("Wait 1000ms...");
    setTimeout(()=>{
        console.log("Wait 500ms...");
        setTimeout(()=>{
            console.log("Wait 100ms...");
        },100)
    },500)
},1000)
```

实际情况中可能是读取文件、发送http请求等；

##### 借助async流程控制工具执行

```shell
npm install async
```

```js
const async=require('async');

//维护一个顺序数组
async.series([
    callback=>{
        setTimeout(()=>{
            console.log("Wawit 1000ms...");
            callback();
        },1000);
    },
    callback=>{
        setTimeout(()=>{
            console.log("Wawit 500ms...");
            callback();
        },500)
    },
    callback=>{
        setTimeout(()=>{
            console.log("Wawit 100ms...");
            callback();
        },100);
    }
]);
```

- 可读性、可维护性更强；
- 刻意回避回调嵌套；

#### （2）实现串行化流程控制

- 按照预期执行的顺序维护一个数组；
- FIFO方法完成任务；
- 每个任务完成以后调用一个函数来返回任务执行的成功与否；

```js
function TaskA(){
    console.log("Doing work A!");
    next();
}

function TaskB(){
    console.log("Doing work B!");
    next();
}

function TaskC(){
    console.log("Doing work C!");
    next();
}

//维护的一个数组；
const tasks=[TaskA,TaskB,TaskC];

function next(err,result){
    if(err) throw err;				   //如果出错，就抛出错误
    const currentTask=tasks.shift();	//没有出错，移动数组；
    if(currentTask){
       currentTask(result);
    }
}

next();
```

#### （3）实现并行化流程控制

> 为了让异步任务并行执行，人需要维护一个数组；但是此时任务的存放顺序无关紧要；

#### （4）利用社区的工具进行流程控制

- Async
- Step
- Seq

## 三、Node Web

- 创建一个新的Web程序
- 搭建RESTful服务
- 持久化数据
- 使用模板

### 1.Node Web程序结构

- package.json  包含依赖项列表和运行这个程序的命令的文件；
- public/             静态资源文件夹，css/客户端js都在这；
- node_modules/ 项目的依赖项会安装到这里；

##### 程序代码

- app.js/index.js          设置程序的代码；
- models/                    数据库模型；
- views/                       用来渲染的页面模板；
- controllers/routes      HTTP请求处理器；
- middleware/              中间件组件；

> 如何组织程序是我的自由，大部分web框架都很灵活；

```shell
npm install --save express
npm rm express --save
```

一个简单的服务器，使用express（）创建一个程序实例，添加路由处理器，然后将实例绑定到一个TCP端口；

```js
const express=require('express');

const app=express();

const port=process.env.PORT || 3000;

app.get('/',(req,res)=>{
    res.send("Hello,world!");
});

app.listen(port,()=>{
    console.log(`Express web app available at localhost:${port}`);
})
```

##### npm脚本

> 启动服务起的命令（`node index.js`）可以保存问npm脚本；如下可以使用`npm start`启动项目；

```json
 "scripts": {
    "start":"node index.js"
  },
```

##### 搭建一个RESTful Web服务

- POST  /articles   
- GET    /articles/:id
- GET    /articles
- DELETE  /articles/:id

```shell
curl http://127.0.0.1:3000/articles/0
curl -X DELETE http://127.0.0.1:3000/articles/0
```

```shell
#官方消息体解析器
npm install --save bodt-parser
```

```js
const express=require('express');
const bodyParser=require('body-parser');

const articles=[{title:'NodeJS入门'},{title:'VueJS入门'},{title:'深入浅出VueJS'}];

const app=express();

app.set('port',process.env.PORT||3000);

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:true}));


app.get('/articles',(req,res,next)=>{
    res.send(articles);
});

app.get('/articles/:id',(req,res,next)=>{
    const id=req.params.id;
    console.log("Fetching article ",id,".");
    res.send(articles[id]);
});

app.delete('/articles/:id',(req,res,next)=>{
    const id=req.params.id;
    console.log("Deleting article ",id,".");
    delete articles[id];
    res.send({message:'Article has been deleted.'});
});

app.post('/articles',(req,res,next)=>{
    const article={title:req.body.title};
    articles.push(article);
    res.send(articles);
});

app.listen(app.get('port'),()=>{
    console.log('App started on port ',app.get('port'));
});

module.exports=app;
```

> 到这一步为止，跟真正的Web程序差不多了，只需要完成两个新的任务：
>
> 永久保存数据到数据库；
>
> 形成可读版本的文章；

```shell
#模板引擎
npm install ejs --save
```

### 2.Node Web开发

> 现代Web开发中，使用Node来进行工具和服务的情况越来越多；
>
> 需要负责和配置维护工具库；
>
> 本章使用npm脚本、Gulp和Webpack搭建易于维护的项目；

#### 前端构建工具的优点：

- 代码简单易懂；
- 支持代码转译；
- 源码映射；

#### Webpck

- 快速搭建支持增量式结构的构建系统；

## 五、服务器端框架

- 使用热门的Node Web框架；
- 选择合适的框架；
- 用Web框架搭建Web程序；

#### 1.用户画像

> 假设一个场景，需要做一个内容分发系统，用户需要上传下载法律文件，在线阅读文件；
>
> 徐娅萍生成PDF还有电子商务组件，你会怎么考虑技术栈？

- 文件上传下载阅读--Express
- 生成PDF的微服务--hapi
- 电子商务组件--SailJS

使用用户画像考虑设计问题是通用做法。





















