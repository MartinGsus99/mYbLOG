---
title: Vue.js实战（8）
date: 2020-12-5 21:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


Ch11 插件

一、插件得创建和使用

```javascript
 //公开的方法install，参数1：VUe构造器，参数2：可选对象     
MyPlugin.install=function(Vue,options){
            //全剧注册组件
            Vue.component('component-name',{
                //组件内容
            })
            //添加实例方法
            Vue.prototype.$Notice=function(){
                //逻辑。。
            }
            //添加全局方法或属性
            Vue.globalMethod=function(){
                //逻辑
            }
            //添加全局混合
            Vue.mixin({
                mounted:function(){
                    //逻辑 
                }
            })
        }
//Vue.use()来使用插件
        Vue.use(MyPlugin)
```

二、前端路由与Vue-router

​		1.实现方式

- 利用url得hash，即所谓的锚点（#）

- HTML5得History模式：需要服务器支持

  2.vue-router基本用法

  ```javascript
  //在webpack项目中安装vue-router
  npm install --save vue-router
  
  import Vue from 'vue'
  import Router from 'vue-router'
  
  Vue.use(Router)
  
  //index.js
  routes: [
      {
        path: '/',
        component: Movie
      },
      {
        path:'/login',
          //一次性全部加载
        component:Login
      },
      {
        path:'/test',
        component:Test
      },
      {
        path:'/index',
        component:(resolve)=>require(['../components/Index.vue'],resolve)
      },
      {
        path:'/about',
          //懒加载（按需加载）mwebpack会把每一个路由打包为一个js文件，当请求到该页面时，才会去加载这个页面得js
        component:(resolve)=>require(['../components/About.vue'],resolve)
      },
      //包含了用户Id得路由，指向同一界面；
       {
        path:'/user/:id',
        component:(resolve)=>require(['../components/User.vue'],resolve)
      }
    ] 
  
  
  ******************************
  
  ```

  3.ES6小语法

  在ES6中，使用let和const代替var来声明变量，const声明常量不可修改；

  let和const得作用域是块（使用了异步路由后，编译出的每个js都叫做快（chunk)）；

  4.小细节

  在router.js中，设置mode为history才会开启HTML5得路由模式，通过’/‘设置路径，否则为’#‘

  5.跳转

  ```vue
  <router-link to="/about">About</router-link>
  
      //页面跳转方法2
      <button @click="changeToMain">Index</button>
      
       methods:{
      changeToMain(){
        //不可以跳转到当前页面路由本身，会报出冗余错误
        this.$router.push('/passage');
      }
    }
  ```

  

- tag:tag可以指定渲染成什么标签，比如tag="li",会渲染成li

- replace：使用后不可以使用返回键回到上一个页面

- go:在history记录中向前或者向后退多少步，参数为整数   this.$router.go(-1)或(2)

三、状态

管理与Vuex

​	1.状态管理与使用场景

```javascript
npm install --save vuex
```

​	2.Vuex得使用

```javascript
//main.js
import Vuex from 'Vuex'

Vue.use(Vuex);

const store=new Vuex.Store({
      state:{
          //定义一个数据
        	count:0
      }
});

//在任何vue文件中都可以获取该数据

```

```vue
<template>
    <div>
        //获取数据
          {{ $store.state.count }}
    </div>
</template>

<script>
export default {
    name:'Counter',
    //使用computed方法显示
    computed:{
        count(){
            return this.$store.state.count;
        }
    }
}
</script>

<style>

</style>
```

3.修改vuex的数据

```vue
const store=new Vuex.Store({
      state:{
        count:0
      },
//首先在store中声明两个mutations
      mutations:{
//increase可以再添加一个参数来控制数值改变的大小；
        increase(state){
          state.count+=1;
        },
        decrease(state){
          state.count-=1;
        }
      }
});


<template>
    <div>
        <button @click="handleIncrease">+1</button>
          {{ count }}
        <button @click="handleDecrease">-1</button>  
    </div>
</template>

<script>
import Button from './Button.vue';
export default {
  components: { Button },
    name:'Counter',
    computed:{
        count(){
            return this.$store.state.count;
        }
    },
    //使用methods方法来调用mutations实现数据修改；
    methods:{
        handleIncrease:function(){
            this.$store.commit('increase');
        },
        handleDecrease:function(){
            this.$store.commit('decrease');
        }
    }
}
</script>
```

ES6小语法：

```javascript
//函数的参数可以设定默认值，当没有传入参数使用默认参数;一个参数不够时，可以传入一个对象，无限扩展；
increase（state，n){
    n=n || 1;
}
```

4.高级用法

