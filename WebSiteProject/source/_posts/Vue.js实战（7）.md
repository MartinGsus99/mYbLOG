---
title: Vue.js实战（7）
date: 2020-12-3 21:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


# Ch10 使用webpack

### 一、webpack基础

​	1.import和export

```javascript
var config={
    version:'1.1.0'
};
export { Config };

export var config={
    versiom:'1.1.0'
};

export function add(a,b){
    return a+b;
};


import { Config } from './config/js'
import { add } from './add.js'

//默认输出
export default{
    
};
```

​	2.npm导入库

​	import Vue from 'vue';

​	import $ from 'jquery';

​	3.webpack基本配置

​		npm init  //初始化

​		npm install webpack --sav-dev //作为开发依赖来安装webpack

​		npm install webpack-dev-server --save-dev //安装开发环境服务器

​		npm dev //启动本服务器

​		webpack --progress --hide-modules //修建模组？

​		npm install css-loader --save-dev

​		npm install style-loader --save-dev

​		npm install extract-text-webpack-plugin --save-dev

​		npm run build //打包

4.箭头函数

render：h=>h(App)等同于：

render:function(h){

return h(App)

}也等同于：

render:h=>{

return h(App);

****}

注：箭头函数里得this指向与普通函数不同，箭头函数得this是定义时得对象，而不是使用时得对象；

5.ES 6语法

```javascript
 components: {
    Title,
    Button,
  },
  
  components:{
      vTitle:Title,
      vButton:Button
  }
```

