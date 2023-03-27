

# Webpack知识体系

- 理解前端工程话概念、工具、目标；
- 团队需要有人熟悉webpack；
- 高阶前端必经之路；

## 一、什么是webpack?

### 1.前端项目构成 

- 多媒体文件
- CSS
- JS
- HTML
- VUE

##### 手动管理

- 比如引入50个js文件，操作过程繁琐；
- 当代码文件之间有依赖时，得严格依赖顺序书写；
- 开发与生产环境一致，很呐接入TS或JS新特性；
- 比较难接入Less、Sass等工具；
- JS、图片、CSS资源管理模型不一致；

### 2.常见工程化工具

- Webpack
- Vite
- RollupJS

### 3. Webpack

##### 功能

- 多份资源文件打包成Bundle；
- 支持Babel、Eslint、TS、CoffeeScript、Less、Sass；
- 支持模块化处理CSS、图片等资源文件；
- 支持HMR+开发服务器；
- 支持持续监听、持续构建；
- 支持代码分离；
- 支持Tree-shaking;
- 支持Sourcemap；

## 二、Webpack

### 1.示例

##### Setp1.安装webpack

```shell

npm i -D webpack webpack-cli
```

##### Setp2.编辑配置文件 webpack.config.js

```js
const path=require('path');

module.exports={
    entry:'./src/index',	//定义当前项目的入口
    mode:"development",
    devtool:false,
    output:{
        filename:'[name].js',			//定义打包后文件的名称；
        path:path.join(_dirname,'./dist')
    }
}
```

Step3.执行编译命令

```shell
npx webpack
```

> 打包到./dist/main.js

### 2.核心流程

- 入口处理：从entry文件开始，启动编译流程；
- 以来解析：从entry开始，根据‘require’ or 'import' 等语句找到依赖资源；
- 资源解析：更具‘module’配置，调用资源转移器，将png、css等非标准js资源转译为js内容；（如何实现？？）
- 资源合并打包：将转译后的资源内容合并打包为可直接在浏览器运行的js文件；

### 3.总结

- 多文件资源合成一个，减少http请求；
- 支持模块化开发；
- 支持高级JS特性；
- 支持TS，CofferScript；
- ...

## 三、使用Webpack--流程类

![](https://s3.bmp.ovh/imgs/2023/02/08/3d52e90c95397aa0.jpg)

### 1.配置文件

Webpack的使用基本都围绕“配置”展开，而这些配置大致可以分为两类：

- 流程类：作用于流程中的某个或多个环节，直接影响打包效果的配置项；

![](https://s3.bmp.ovh/imgs/2023/02/08/175cc632cc5489e6.jpg)

- 工具类：主流程之外，提供更多工程化能力的配置项；

### 2.必须配置

> 在一个项目配置里面，至少需要entry和output

```js
const path=require('path');

module.exports={
    entry:'./src/index',	//定义当前项目的入口
    output:{
        filename:'[name].js',			//定义打包后文件的名称；
        path:path.join(_dirname,'./dist')
    }
}
```

### 3.处理CSS

- 安装loader

```shell
npm add -D css-loader style-loader
```

- 添加module处理css文件

```js
const path=require('path');

module.exports={
    entry:'./src/index',	//定义当前项目的入口
    output:{
        filename:'[name].js',			//定义打包后文件的名称；
        path:path.join(_dirname,'./dist')
    }，
    module:{
    	//css处理器
    	rules:[{
            test:/\.css$/,				//css文件名过滤条件，满足即处理
            use:[						//使用怎样的loader去处理
            "style-loader",
            "css-loader"
            ]
        }]
	}
}
```

- 引入

```js
const styles=requrie("./index.css");

import styles from './index.css';
```

##### loader有什么用？



##### 与旧时代html中维护css相比，使用loader有什么优劣？



##### 如何在webpack接入Less，Sass，Stylus等？



### 4.接入Babel

> 将ES6代码转译为ES5，向下兼容；

- 安装依赖

```shell
npm i -D @babel/core @babel/preset-env babel-loader
```

- 声明产物出口`output`

```js
const path=require('path');

module.exports={
    entry:'./src/index',	//定义当前项目的入口
    output:{
        filename:'[name].js',			//定义打包后文件的名称；
        path:path.join(_dirname,'./dist')
    }，
    module:{
    	//css处理器
    	rules:[{
           		test:/\/js$/,
    			user:[
    					loader:'babel-loader',
    					options:{
    							presets:[
    							['@babel/preset-env']
                                ]
                            }
                     ]
            ]
        }]
	}
}
```

- 执行`npx webpack`

##### 问题

- Babel具体由什么功能？
- Babel与Webpack分别解决了什么问题？为何两者能协作到一块儿？

### 5.生成HTML

> 自动生成HTML文件；

- 安装依赖

```shell
npm i -D html-webpack-plugin
```

- 声明产物出口`output`

```js
const path=require('path');

module.exports={
    entry:'./src/index',	//定义当前项目的入口
    output:{
        filename:'[name].js',			//定义打包后文件的名称；
        path:path.join(_dirname,'./dist')
    }，
    plugins:[new HtmlWebpackPlugin()]
};
```

- 执行`npx webpack`

##### 问题

- 相比于手工维护HTML内容，这张方式有什么优缺点？

## 四、使用web pack--工具类

### 1. HMR Hot Module Replacement

> 模块热替换，写完的代码能立刻更新到页面；

- 开启HMR

  ```js
  devServer:{
  	hot:true,
  	open:true
  },
  module:{
      
  },
  watch:true
  ```

- 启动Webpack

```shell
npx webpack serve
```

### 2.Tree-shaking

> 删除没有使用到的代码

- Dead Code：代码没有被用到，不可到达；代码的执行结果不会被用到；代码只读不写；
- Tree-shaking：模块导出了但是没被使用；

```js
mode:"production",
optimization:{
usedExports:true,
}
```

## 五、其他工具

- 缓存
- Sourcemap
- 性能监控
- 日志
- 代码压缩
- 分包
- ...

## 六、理解Loader

### 1.Webpack只认识JS

> 为了处理非标准JS资源，设计出资源翻译模块---Loader
>
> 用于将资源翻译为标准JS

### 2.使用loader

- 安装依赖

```shell
npm add -D css-loader style-loader less-loader
```

- 添加`module`处理css文件

### 3.认识loader：链式调用

- less-loader：将less=>css;
- css-loader：将css包装成类似module.exports="${css}"的内容，包装后的内容符合JS语法；
- style-loader：将css模块包进require语句，并在运行时调用injectStyle等函数将内容注入到页面的style标签；

![](https://s3.bmp.ovh/imgs/2023/02/08/d65b92e7cb18342c.jpg)

### 4.loader特点

- 链式执行；
- 支持异步执行；
- 分normal、patch两种模式；

### 5.常见loader

![](https://s3.bmp.ovh/imgs/2023/02/08/fe2e05bc32513a45.jpg)

##### 问题

- Loader是什么？要求的输出是什么？
- Loader的链式调用是什么意思？如何串联多个loader？
- Loader中如何处理异步场景？

## 七、理解插件

> 很多知名工具，如vscode、chrome、vue等都涉及了所谓的“插件架构“为什么？

- 心智成本高=>可维护性低=>生命力弱
- 插件架构精髓：对拓展开发，对修改封闭；
- Webpack很多功能都是基于插件的概念实现；

### 1.使用插件

```js
//引入插件
const DashboardPlugin=require('webpack-dashboard/plugin');

module.exports={
    //添加插件实例
    plugins:[new DashboardPlugin()];
};
```

### 2.编写插件

##### 钩子

```js
class SomePlugin{
    apply(complier){
        complier.hooks.thisCompilation.tap('SomePlugin',(compilation)=>{
            
        })
    }
}
```

- 时机：编译过程的特定节点，webpack会以钩子的形式通知插件此刻正在发生什么事；
- 上下文：通过tapable提供的回调机制，以参数的方式传递上下文信息；
- 交互：在上下文参数对象中附带了很多存在side effect 的交互接口，插件可以通过这些接口改变；

##### 问题

- Loader与插件有什么区同点？
- 钩子有什么作用？如何监听钩子函数？

## 八、学习方法



![](https://s3.bmp.ovh/imgs/2023/02/08/979e56c5c207eac0.jpg)

![](https://s3.bmp.ovh/imgs/2023/02/08/452e2397f71ff64e.jpg)

















