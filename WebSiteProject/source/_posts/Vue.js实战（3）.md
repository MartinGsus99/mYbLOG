---
title: Vue.js实战（3）
date: 2020-11-20 17:38:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/bg4.jpeg
---

# Ch5 内置指令

### 5.1 基本指令


1.v-cloak
网速较慢时，vue.js还没有加载完成，页面会显示空内容，用v-cloak解决；



```html
<div id="app" cloak>
    {{ content }}
</div>

[cloak]{
display:none;
}
```

2.v-once

仅仅渲染一次，首次渲染后，不在随数据的变化而变化，视为静态内容；

3.v-if、v-else-if、v-else

```html
<div id="app">
    <a v-if="status===1">显示状态1</a>
    <a v-else-if="status===2">显示状态2</a>
    <a v-else="status===3">显示状态3</a>
    //判断多个元素，使用<template></template>
</div>
```

一个简单的切换按钮效果

```html
   <div id="app">
        <template v-if="type=== 'name'">
            <input type="text" placeholder="name">
        </template>

        <template v-else>
            <input type="email" placeholder="xxx@xx.com">
        </template>
        <button @click="changeMode">切换</button>
    </div>
    
    
    <script>
        var app=new Vue({
            el:"#app",
            data:{
                type:'name',
            },
            methods:{
                changeMode:function(){
                    this.type=this.type==='name'?'mail':'name';
                }
            }
        })
    </script>
```

4.v-show:与if基本一致，但是不可以用在'''\<template>\</template>'''

区别：v-if只有为true的时候才会编译渲染，而v-show只是css属性切换，一定会编译，适用于经常切换的场合；



5.v-for：数组遍历及枚举

```html
 <div>
            <li v-for="book in books">{{ book.name }}</li>
        </div>
 data:{
		books:[
	{ name: '<Book1>' },
    { name: '<Book1>' },
    { name: '<Book1>' }, 
    ]
    },
```

### 5.3过滤与排序：使用计算属性返回处理后的数组

筛选数据：

```html
         computed:{
                filterBooks:function(){
                    return this.books.filter(function(book){
                        return book.name.match(/Book2/);
                    })
                }
```

### 5.4 方法与事件

```html
//一个小的计数器
 <div>
            点击次数：{{ counter }}
            <button @click="counter++">Click</button>
            <button @click="add10">Click +10</button>
            <button @click="reset_counter">Reset</button>
        </div>

<script>
     add10:function(){
                    this.counter+=10;
                },
     reset_counter:function(){
                     this.counter=0;
                }
</script>
```

5.4.2 修饰符

修饰符

| .stop  | .prevent | .capture |
| ------ | -------- | :------- |
| .self  | .once    | .enter   |
| .tab   | .delete  | .esc     |
| .space | .up      | .down    |

