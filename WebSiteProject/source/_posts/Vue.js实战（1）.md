---
title: Vue.js实战（1）
date: 2020-11-17 21:33:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/bg3.jpg
---


# Ch1

功能：

解耦视图与数据

可复用组件

前端路由

状态管理

虚拟Dom

### 1.MVVM模式（Model-View-View-Model）

# Ch2

## 一、Vue实例与数据绑定

### 1.数据绑定

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <script src="./js/vue.js"></script>
</head>
<body>
    <div id="app">
    	//插值{{}}
        Welcome to home:{{ home }}
    </div>

    <script>
        var app=new Vue({
            el:"#app",
            data:{
                home:' http://www.lishengwang.top',
            }
        })
    </script>
</body>
</html>
```

### 2.生命周期

​	a.created:完成数据观测，未挂载；

​	b.mounted：el挂载到实例；

​	c.beforeDestory：实例销毁前，解绑addEventListener监听事件等；

### 3.v-html

```html
 <span v-html="html1"></span>
 
   <script>
        var app=new Vue({
            el:"#app",
            data:{
                home:' http://www.lishengwang.top',
                html1:'<a href="http://www.lishengwang.top">Click!</a>'
            }
        })
    </script>
```

### 4.filter过滤器

```vue
{{ a|b }}
```

## 二、指令与事件

​	1.v-if

```html
  <div v-if="show">
            V-if实例
  </div>
        
   data:{
                show:true
            },
```

​	2.v-bind:绑定数据，随数据变化进行更新

```
 <a v-bind:href="home">V-bind</a>
```

​	3.v-on：绑定事件

```html
  <div v-if="show">
            V-if实例
        </div>
        <div>
            <button v-on:click="notToShow">点击隐藏</button>
            <button v-on:click="toShow">点击显示</button>
        </div>
        
     methods:{
                notToShow:function(){
                    this.show=false
                },
                toShow:function(){
                    this.show=true
                }
```

​	4.v-model:绑定数据

​	  

```html
  <div>
            Name：{{ good.name }}
            Price: {{ good.price }}
            Count: {{ good.count }}

            All in: {{ all_price }}
        </div>
        <div>

            <span>新价格：<input type="text" v-model="good.price"></span>
            </br>
            <span>新数量：<input type="text" v-model="good.count"></span>
        </div>
```

4.语法糖

​	（1）

```html
 #v-on ===> @
 <button v-on:click="notToShow">点击隐藏</button>
 <button @click="notToShow">点击隐藏</button>
 
 #v-bindd ===> :
 <a v-bind:href="#"></a>
 <a :href="#"></a>
```

