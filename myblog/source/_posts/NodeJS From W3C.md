# Node JS From W3C

## 一、NodeJS回调函数

> 异步编程依托于回调来实现；
>
> 回调函数完成任务后会被调用，Node使用了大量得回调函数，Node所有Api都支持回调函数；
>
> 例如，我们可以一边读取文件，一边执行其他命令，在文件读取完成后，我们将文件内容作为回调函数的参数返回。这样在执行代码时就没有阻塞或等待文件 I/O 操作。这就大大提高了 Node.js 的性能，可以处理大量的并发请求。

```js
function foo1(name,age,callback){}
function foo2(value,callback1,callback2){}
```

```js
//阻塞代码实例
var fs=require("fs");
var data=fs.readFileSync('../../assets/test.txt');
console.log(data.toString());
console.log("Program Ended");


//非阻塞代码实例
var fs=require("fs");
fs.readFile('../../assets/test.txt',function(err,data){
    if(err) return console.error(err);
    console.log(data.toString());
});
console.log("Program Ended");
```

第一个实例在文件读取完之后才执行；第二个实例我们不需要等待文件读取完；可以在读取文件的同时处理其他逻辑；

## 二、NodeJS事件循环

### 1.events

> NodeJS是单进程单线程应用程序，但是因为V8引擎提供得异步执行回调接口，通过这些接口可以处理大量并发，性能较高；
>
> Node.js 基本上所有的事件机制都是用设计模式中观察者模式实现。
>
> Node.js 单线程类似进入一个while(true)的事件循环，直到没有事件观察者退出，每个异步事件都生成一个事件观察者，如果有事件发生就调用该回调函数.
>
> Node.js使用事件驱动模型，当web server接收到请求，就把它关闭进行处理，然后服务下一个web请求；
>
> 请求完成，放回处理队列，当到达队列开头，将结果返回给用户；
>
> webserver 一直接受请求而不等待任何读写操作。（这也称之为非阻塞式IO或者事件驱动IO）

```js
//引入events模块；
var events=require('events');
//创建eventEmitter对象
var eventEmitter=new events.EventEmitter();

//绑定事件及事件得处理程序
eventEmitter.on('eventName',eventHandler);

//触发事件
eventEmitter.emit('eventName');
```

```js
//引入events模块
var events=require('events');
//创建eventEmitter对象
var eventEmitter=new events.EventEmitter();
//创建事件处理程序
var connectHandler=function connected(){
    console.log('连接成功。');
    //触发data_received事件
    eventEmitter.emit('data_received');
}
//绑定connection事件处理程序
eventEmitter.on('connection',connectHandler);
//使用匿名函数绑定data_received事件
eventEmitter.on('data_received',function(){
    console.log('数据接收成功。');
});
//触发connection事件
eventEmitter.emit('connection');
console.log("程序执行完毕。");
```

### 2.Node是如何工作的？

> Node应用程序中，执行异步操作得函数将回调函数作为最后一个参数，回调函数接受错误对象作为第一个参数；

```js

var fs=require("fs");
//将回调函数作为最后一个参数， 回调函数接收错误对象作为第一个参数。
fs.readFile('../../assets/test.txt',function(err,data){
    if(err) return console.error(err);
    console.log(data.toString());
});
console.log("程序执行完毕");
```

### 3.EventEmitter

> Node.js得所有异步I/O操作都会在完成时返回一个事件到事件队列；
>
> Node.js里面得许多对象都会分发事件，所有这些事件得对象都是events.EventEmitter的实例；

#### EventEmitter类：事件触发与事件监听器功能的封装

```js
var EventEmitter=require('events').EventEmitter;
var event=new EventEmitter();
event.on('some_event',function(){
    console.log('some_event 事件触发');
});
event.on('some_event',function(){
    console.log("Martin wang 的事件触发了");
});
setTimeout(function(){
    event.emit('some_event');
},1000);
```

原理：event对象注册了事件some_event的一个监听器，然后1000ms后向event对象发送事件some_event此时调用其监听器；

EventEmitter的每个事件由一个事件名和若干参数组成，事件名是一个字符串；每个事件支持若干个事件监听器；

两个事件监听器回调函数被先后调用；

```js
var events=require('events');
var emitter=new events.EventEmitter();

//监听器1
var listener1=function listener1(){
    console.log('监听器listener1执行');
}   
//监听器2
var listener2=function listener2(){
    console.log('监听器listener2执行');
}
//绑定connection事件，处理函数为listener1   
emitter.addListener('connection',listener1);
//绑定connection事件，处理函数为listener2
emitter.on('connection',listener2);
var eventListeners=require('events').EventEmitter.listenerCount(emitter,'connection');
console.log(eventListeners+"个监听器监听连接事件。");
//处理connection事件
emitter.emit('connection');
//移除绑定的listener1函数   
emitter.removeListener('connection',listener1);
console.log("listener1不再受监听。");
//触发连接事件
emitter.emit('connection');
eventListeners=require('events').EventEmitter.listenerCount(emitter,'connection');
console.log(eventListeners+"个监听器监听连接事件。");
console.log("程序执行完毕。");
```

### 4.继承EventEmitter

> 大多数时候我们不会直接使用 EventEmitter，而是在对象中继承它。包括 fs、net、 http 在内的，只要是支持事件响应的核心模块都是 EventEmitter 的子类。
>
> 为什么要这样做呢？原因有两点：
>
> 首先，具有某个实体功能的对象实现事件符合语义， 事件的监听和发生应该是一个对象的方法。
>
> 其次 JavaScript 的对象机制是基于原型的，支持 部分多重继承，继承 EventEmitter 不会打乱对象原有的继承关系。

## 三、NodeJS Buffer

> JS语言自身只有字符串数据类型，没有二进制数据类型；
>
> 但是处理TCP流或者文件流时，必须使用二进制数据；因此NodeJS定义了一个Buffer类，创建一个专门存放二进制数据的缓存区；

### 1.Buffer与字符编码

> Buffer实例一般用于表示编码字符的序列，比如UTF-8等；

```js
const buf=Buffer.from('hello world','ascii');
console.log(buf.toString('hex'));
console.log(buf.toString('base64'));
```

### 2.Buffer类

```js
//创建长度为10字节的Buffer实例
const buf1=Buffer.alloc(10);
//创建长度为10字节，且用0填充的Buffer实例
const buf2=Buffer.alloc(10,1);
//创建长度为10字节，且未初始化的Buffer实例
const buf3=Buffer.allocUnsafe(10);
//创建一个包含[0x1,0x2,0x3]的Buffer实例
const buf4=Buffer.from([1,2,3]);
//创建一个包含UTF-8字节[0x74,0x65,0x73,0x74]的Buffer实例
const buf5=Buffer.from('test');
//创建一个包含Latin-1字节[0x74,0x65,0x73,0x74]的Buffer实例
const buf6=Buffer.from('test','latin1');

```

### 3.写入缓冲区

```js
buf.write(string[,offset[,length]][,encoding])
// string 字符串
// offset 开始写入的索引值
// length 写入的字节数
// encoding 编码方式
buf.write('hello world');
console.log(buf.toString());
console.log(buf.toJSON());
console.log(buf.toString('base64'));
//缓冲区合并
const buffer1=Buffer.from(('菜鸟教程'));
const buffer2=Buffer.from(('www.runoob.com'));
const buffer3=Buffer.concat([buffer1,buffer2]);
console.log("buffer3 内容: "+buffer3.toString());
//缓冲区比较
const buffer4=Buffer.from('ABC');
const buffer5=Buffer.from('ABCD');
const result=buffer4.compare(buffer5);
if(result<0){
    console.log(buffer4+"在"+buffer5+"之前");
}else if(result==0){
    console.log(buffer4+"与"+buffer5+"相同");
}else{
    console.log(buffer4+"在"+buffer5+"之后");
}
//拷贝缓冲区
const buffer6=Buffer.from('ABC');
//拷贝一个缓冲区
const buffer7=Buffer.alloc(3);
buffer6.copy(buffer7);
console.log("buffer7 content: "+buffer7.toString());
//缓冲区裁剪
const buffer8=Buffer.from('runoob');
//剪切缓冲区
const buffer9=buffer8.slice(0,2);
console.log("buffer9 content: "+buffer9.toString());
```

方法名参考JS的字符串处理；

## 四、NodeJS Stream

> Stream是一个抽象接口，node中很多对象实现了这个接口；
>
> 例如对http服务器发起请求的request对象就是一个stream还有stdout；





























