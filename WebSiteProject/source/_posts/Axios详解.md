---
title: Axios详解
date: 2022-10-27 16:09:00
categories: 
    - JS
tags: 
    - JS
mp3: 
cover: img/axios.png
---

# Axios

#### 基于promise可以用于浏览器和node.js的网络请求库

### 一、基础定义Promise

#### 1.promise

一个对象，用于传递异步操作的消息；本意上可以理解为，承诺过一段时间返回一个结果。

```visual basic
 其实就是一个请求发出去以后，并不能马上获得需要的数据，因此整个js代码需要暂停等待请求数据的返回
```

Promise有三种状态：pending(等待态)，fulfiled(成功态)，rejected（失败态）；状态一旦改变就不会再变；创造promise实例后会立即执行；

```js

// 当参数a大于10且参数fn2是一个方法时 执行fn2
function fn1(a, fn2) {
    if (a > 10 && typeof fn2 == 'function') {
        fn2()
    }
}
fn1(11, function() {
    console.log('this is a callback')
})
```

一般来说我们会碰到的回调嵌套都不会很多，一般就一到两级，但是某些情况下，回调嵌套很多时，代码就会非常繁琐，会给我们的编程带来很多的麻烦，这种情况俗称——回调地狱。

这时候我们的promise就应运而生、粉墨登场了

promise主要解决两个问题：

1. 回调地狱，代码难以维护，常常第一个函数的输出是第二个函数的输入；

2. 支持多个并发请求，并从请求中获取数据；可以解决异步的问题；

   ```visual basic
   建议使用ES6箭头函数的编码方式，获得数据，处理数据，处理完成，下一步~
   ```

   

#### 2.promise用法

```js
let p=new Promise((resolve,reject)=>{
    //一些异步操作
    setTimeout(()=>{
        console.log("Finished.");
        resolve("成功！")；
    }，2000)
})

//promise的构造函数接受一个函数类型的参数，并且需要传入两个参数：
resolve：异步操作执行成功之后的回调函数；
reject：异步操作执行失败后的回调函数；
```

then 链式操作：

表面上，promise只是简化层层回调，实质上，用维护状态、传递状态的方法使得回调函数能够及时调用；

正确场景：

```javascript
p.then((data))=>{
    cosnsole.log(data);
}).then((data)=>{
    console.log(data);
}).then((data)=>P{
        console.log(data);
        });
```

#### 3.reject用法

把promise的状态设置为rejected，这样在then中就能捕捉到，然后执行“失败”情况的回调；

```js
let p=new Promise((resolve,reject)=>{
    setTimeout(function(){
        var num=Math.ceil(Math.random()*10);
        if(num<=5)
            {
                resolve(num);
            }else
                {
                    reject("数字太大！")；
                }
    },2000);
})；
p.then((data)=>{
    console.log("Resolved",data);
},(err)=>{
    console.log("Rejected",err);
}
      )
```

#### 4.catch用法

catch和then的第二个参数一样用来指定reject的回调；

```js
p.then((data)=>{
    console.log("Resolved",data);
}).catch((err)=>{
    console.log("Rejected",err);			//抛出异常
})
//如果执行resolve的回调时，如果抛出异常，并不会报错停止js，而是进入到catch方法；
p.then((data) => {
    console.log('resolved',data);
    console.log(somedata); //此处的somedata未定义
})
.catch((err) => {
    console.log('rejected',err);
});
```

#### 5.all的用法

谁跑得慢，以谁为准执行回调；all接受一个数组参数，里面的值最终都算返回Promise对象；

all方法提供了并行执行异步操作的能力，并且在所有异步操作执行完成之后才执行回调；

```js
let Promose1=new Promise(function(resolve,reject){})
let Promise2=new Promise(function(resolve,reject){})
let Promise3=new Promise(function(resolve,reject){})

let p=Promise.all([Promise1,Promise2,Promise3])

p.then(function(){
   	console.log("三个都执行成功则成功")
},function(){
    console.log("只要有失败则失败")
})
```

使用场景：一个游戏需要很多素材，只有所有素材都下载到本地之后，才开始初始化；

```js
let video=new Promise(funcion(resolve,reject){});
let word=new Promise(function(resolve,reject){});

let p=Promise.all([video,word]);

p.them(funcion(){
       console.log("开始初始化！");
       },function(){
           console.log("游戏初始化失败")；
       })
```

#### 6.race用法

谁跑的块，以谁为准执行回调；

可以用race给某个异步请求设置超时时间，并且在超时后执行相应的操作，代码如下：

```js
function requestImg(){
	var p = new Promise((resolve,reject)=>{
        var img =new Img();
        img.onload=function(){
            resolve(img);
        }
        img.src='img path';
    });
    return p;
}

//延时函数，用于计时
function timeout(){
    var p=new Promise((resolve,reject)=>{
        setTimeout(()=>{
            reject("请求图片超时！");
        },5000);
    });
    return p;
}
//调用
Promise.race([requestImg(), timeout()]).then((data) =>{
    console.log(data);
}).catch((err) => {
    console.log(err);
});
```

### 二、基础定义Axios

#### 服务端它使用原生 node.js `http` 模块, 而在客户端 (浏览端) 则使用 XMLHttpRequests。

#### 1.特性

- 从浏览器创建 [XMLHttpRequests](https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest)
- 从 node.js 创建 [http](http://nodejs.org/api/http.html) 请求
- 支持 [Promise](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise) API
- 拦截请求和响应
- 转换请求和响应数据
- 取消请求
- 自动转换JSON数据
- 客户端支持防御[XSRF](http://en.wikipedia.org/wiki/Cross-site_request_forgery)

#### 2.安装使用

```shell
npm install axios
//yarn
 yarn add axios
```

#### Get请求

```js
const axios=require('axios');

//向给定的ID用户发起请求
axios.get('/user?ID=12345').then(function(response){
    console.log("成功！")
}).catch(function(err){
    console.log("失败");
}).then(function(){
    console.log("总是执行的部分");
})

//以上代码可以等价于
axios.get('/user',{
    params:{
        ID:12345
    }
}).then(function(response){
    console.log("成功！")
}).catch(function(err){
    console.log("失败");
}).then(function(){
    console.log("总是执行的部分");
})

```

#### POST请求

```js
axios.post('/user',{
    fiestName:'Fred',
    lastName:'Smith'
}).then(function(response){
    console.log(response);
}).catch(function(err){
    console.log(err);
});

//多个POST请求
function getUserAccount(){
    return axios.get('/user/12345');
}

function getUserPermissions(){
    return axios.get('/user/12345/permissions');
}

Promise.all([getUserAccount(),getUserPermissions()]).then(function(results){
    const acct=results[0];
    const perm=results[1];
})
```

#### 3.Axops API

可以向 `axios` 传递相关配置来创建请求

```js
//发起一个post请求
axios({
	method:'post',
    url:'/user/12345',
    data:{
        firstname:'Martin',
        lastname:'Smith'
    }
});
```

```js
//在nodeJS用GET请求远程图片
axios({
    method:'get',
    url:'http://test/123',
    responseType:'stream'
}).then((response)=>{
    response.data.pipe(fs.createWriteStream('test.jpg'));
});
```

#### 4.请求配置

创建请求时可以用配置选项；只有url是必须的，如果没有指定method，则默认使用GET；

```json
{
    url:'/api/user',          //用于请求的服务器URL
    method:'get',
    baseUrl:'https://192.168.0.1:35000',		//自动加在url前；
    transformRequest:[
        function(data,headers){
            //对即将发送的data进行处理；
            return processedData;
        }
    ],
    transformResponse:[
        function(response){
            //对收到的响应进行处理；
            return processedResponse;
        }
    ],
    headers:{'X-Requested-With': 'XMLHttpRequest'},
    params:{
        ID:12345		//与请求一起发送的url参数；
    }，
    //data是作为请求体被发送的数据，仅适用于PUT，POST，DELETE和PATCH方法；
    // 在没有设置 `transformRequest` 时，则必须是以下类型之一:
  	// - string, plain object, ArrayBuffer, ArrayBufferView, URLSearchParams
  	// - 浏览器专属: FormData, File, Blob
  	// - Node 专属: Stream, Buffer
    data:{
    firstname:'Fred',
	},
      // 发送请求体数据的可选语法
      // 请求方式 post
      // 只有 value 会被发送，key 则不会
      data: 'Country=Brasil&City=Belo Horizonte',

	//timeout:指定请求超时的毫秒数；默认0ms；
	timeout:1000,  
	
	//跨域时是否需要凭证；
	withCredentials:false,
  // `adapter` 允许自定义处理请求，这使测试更加容易。
  // 返回一个 promise 并提供一个有效的响应 （参见 lib/adapters/README.md）。
  adapter: function (config) {
    /* ... */
  },

  // `auth` HTTP Basic Auth
  auth: {
    username: 'janedoe',
    password: 's00pers3cret'
  },

  // `responseType` 表示浏览器将要响应的数据类型
  // 选项包括: 'arraybuffer', 'document', 'json', 'text', 'stream'
  // 浏览器专属：'blob'
  responseType: 'json', // 默认值

  // `responseEncoding` 表示用于解码响应的编码 (Node.js 专属)
  // 注意：忽略 `responseType` 的值为 'stream'，或者是客户端请求
  // Note: Ignored for `responseType` of 'stream' or client-side requests
  responseEncoding: 'utf8', // 默认值

  // `xsrfCookieName` 是 xsrf token 的值，被用作 cookie 的名称
  xsrfCookieName: 'XSRF-TOKEN', // 默认值

  // `xsrfHeaderName` 是带有 xsrf token 值的http 请求头名称
  xsrfHeaderName: 'X-XSRF-TOKEN', // 默认值

  // `onUploadProgress` 允许为上传处理进度事件
  // 浏览器专属
  onUploadProgress: function (progressEvent) {
    // 处理原生进度事件
  },

  // `onDownloadProgress` 允许为下载处理进度事件
  // 浏览器专属
  onDownloadProgress: function (progressEvent) {
    // 处理原生进度事件
  },

  // `maxContentLength` 定义了node.js中允许的HTTP响应内容的最大字节数
  maxContentLength: 2000,

  // `maxBodyLength`（仅Node）定义允许的http请求内容的最大字节数
  maxBodyLength: 2000,

  // `validateStatus` 定义了对于给定的 HTTP状态码是 resolve 还是 reject promise。
  // 如果 `validateStatus` 返回 `true` (或者设置为 `null` 或 `undefined`)，
  // 则promise 将会 resolved，否则是 rejected。
  validateStatus: function (status) {
    return status >= 200 && status < 300; // 默认值
  },

  // `maxRedirects` 定义了在node.js中要遵循的最大重定向数。
  // 如果设置为0，则不会进行重定向
  maxRedirects: 5, // 默认值

  // `socketPath` 定义了在node.js中使用的UNIX套接字。
  // e.g. '/var/run/docker.sock' 发送请求到 docker 守护进程。
  // 只能指定 `socketPath` 或 `proxy` 。
  // 若都指定，这使用 `socketPath` 。
  socketPath: null, // default

  // `httpAgent` and `httpsAgent` define a custom agent to be used when performing http
  // and https requests, respectively, in node.js. This allows options to be added like
  // `keepAlive` that are not enabled by default.
  httpAgent: new http.Agent({ keepAlive: true }),
  httpsAgent: new https.Agent({ keepAlive: true }),

  // `proxy` 定义了代理服务器的主机名，端口和协议。
  // 您可以使用常规的`http_proxy` 和 `https_proxy` 环境变量。
  // 使用 `false` 可以禁用代理功能，同时环境变量也会被忽略。
  // `auth`表示应使用HTTP Basic auth连接到代理，并且提供凭据。
  // 这将设置一个 `Proxy-Authorization` 请求头，它会覆盖 `headers` 中已存在的自定义 `Proxy-Authorization` 请求头。
  // 如果代理服务器使用 HTTPS，则必须设置 protocol 为`https`
  proxy: {
    protocol: 'https',
    host: '127.0.0.1',
    port: 9000,
    auth: {
      username: 'mikeymike',
      password: 'rapunz3l'
    }
  },

  // see https://axios-http.com/zh/docs/cancellation
  cancelToken: new CancelToken(function (cancel) {
  }),

  // `decompress` indicates whether or not the response body should be decompressed 
  // automatically. If set to `true` will also remove the 'content-encoding' header 
  // from the responses objects of all decompressed responses
  // - Node only (XHR cannot turn off decompression)
  decompress: true // 默认值
}

```

#### 5.响应结构

```json
{
	//data为服务器响应
    data:{},
    
    //状态码
    status:200,
    
    //HTTP状态信息
    statusText:'OK',
    
    //服务器响应头
    headers:{},
    //axios请求的配置信息；
    config:{},
    //生成响应的请求
    // 在node.js中它是最后一个ClientRequest实例 (in redirects)，
  	// 在浏览器中则是 XMLHttpRequest 实例
    request:{},
}
```



### 三、默认配置

#### 1.全局axios默认值

```js
axios.defaults.baseURL = 'https://api.example.com';
axios.defaults.headers.common['Authorization'] = AUTH_TOKEN;
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
```

#### 2.自定义实例默认值

```js
// 创建实例时配置默认值
const instance = axios.create({
  baseURL: 'https://api.example.com'
});

// 创建实例后修改默认值
instance.defaults.headers.common['Authorization'] = AUTH_TOKEN;
```

#### 3.配置的优先级

```js
//此时默认超时时间为0
const instance=axios.create();

//重写库的超时默认值
instance.defaults,timeout=2500;

//重写超时时间
instance.get('/logout',{
    timeout:5000
});
```

#### 4.拦截器

请求或者响应被then或者catch处理之前拦截

```js
//添加请求拦截器
axios.interceptors.request.user(function(config){
    //发送请求前做点啥~
    return config;
},function(error){
    //对发送中的错误做点啥~
    return Promise.reject(error);
});

//添加响应拦截器
axios.interceptors.response.user(function(response){
    //2xx范围内的状态码都会触发此函数哦~
    //do something.
    return response;
},function(error){
    //2xx以外的状态码都会触发此函数哦~
    //do something.
    return error;
});
```

##### 移除拦截器

```js
const interceptor=axios.interceptors.request.user(function(){

});
axios.interceptors.request.eject(interceptor);
```

##### 添加拦截器

```js
const instance = axios.create();
instance.interceptors.request.use(function () {/*...*/});
```

#### 5.错误处理

```js
axios.get('/user/12345').catch(function(error){
    if(error.response){
        //请求成功发出且服务器响应了状态码，但是状态码超出了2xx
        console.log(error.response.data);
    }else if(error.request){
        //请求已经发起成功，但是没有收到响应；
        //error.request是浏览器中XMLHttpRequest的实例；
        console.log(error.request);
    }else{
        //请求发出时出问题
        console.log('Error:',error.message);
    }
    console.log(error.coonfig);
})
```

##### 使用validataStatus配置选项，可以自定义抛出错误HttpCode;

```js
axios.get('/user/12345',{
    validateStatus:function(status){
        return status>500;
    }
})
```

##### 使用 `toJSON` 可以获取更多关于HTTP错误的信息。

```js
axios.get('/user/12345')
  .catch(function (error) {
    console.log(error.toJSON());
  });
```

#### 6.取消请求

##### fetechAPI  AbortController取消请求

```js
const comtrollor=new AbortController();

axios.get('/foo/bar',{
    signal:controller.singal
}).then(function(response){
    
});

controllor.abort();
```

##### CancelToken deprecated(已弃用)

#### 7.请求体编码

默认情况下，axios将js对象序列化为json；

以`application/x-www-form-urlencoded`格式发送数据；

##### 浏览器

```js
const params=new URLSearchParams();
params.append('param1','value1');
params.append('params2','value2');
axios.post('/foo',params);

//注意，并不是所有的浏览器都支持URLResearchParams

//qs库编码数据
const qs=require('qs');
axios.post('/foo',qs.stringify({
    'bar':123
}));

或者ES6方法

import qs from 'qs';
cosnt data={
    'bar':123
};

const options={
    method:'POST',
    headers:{ 'content-type': 'application/x-www-form-urlencoded' },
    data:qs.stringify(data),
    url,
};
axios(options);
```

##### NodeJS 使用querystring

```js

const querystring = require('querystring');
axios.post('http://something.com/', querystring.stringify({ foo: 'bar' }));

const url = require('url');
const params = new url.URLSearchParams({ foo: 'bar' });
axios.post('http://something.com/', params.toString());

//如果需要对嵌套对象进行字符串化处理，则最好使用 qs 库，因为 querystring 方法在该用例中存在已知问题
```

Form Data

```js
const FormData=require('form-data');

const form =new FormData();
form.append('filed1','value1');

axios.post('https://example.com',form,{headers:from.getHeaders()})
```

拦截器

```js
axios.interceptors.request.use(config=>{
    if(config.data instanceof FormData){
        Object.assign(config.headers,config.data.getHeaders());
    }
    retun config;
})
```

























