---
title: Vue.js实战（2）
date: 2020-11-18 21:33:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


# Ch3 计算属性

1.计算属性：遇到复杂的逻辑时，使用计算属性；将所有的计算属性以函数的形式卸载Vue实例的computed属性内，返回计算结果；

```
  <div>
            {{ reversedText }}
        </div>

  <script>
            data:{
                text: '123,456',
            },
            computed:{
                reversedText: function(){
                    return this.text.split(',').reverse().join(',');
                }
</script>
```

2.用法

计算属性可以依赖多个vue实例的数据，只要其中一个数据发生变化，计算属性就会重新执行，视图也会更新；

3.和methods的区别

```
<div>
    {{ reversedText }}
</div>

<scirpt>
    methods:{
        reverserText:function(){
            return this.text.split(',').reverser().join(',');
        }
    },
    computed:{
         reversedText: function(){
             return this.text.split(',').reverse().join(',');
    }
</scirpt>
```

两者实现了相同的效果，但是计算属性是基于依赖缓存，一个依赖数据发生变化，才会重新取值；methods只要重新渲染，就会调用；

当遍历大数组和做大量计算时，应使用计算属性，除非不用缓存；

# CH4 v-bind及class与style的绑定

1.v-bind指令

```
<div>
    <a v-bind:href="url">链接</a>
    <img v-bind:src:="imageUrl"/>

     <a :href="url">链接</a>
    <img :src="imageUrl"/>
</div>

<script>
    data:{
        url:'...',
        imageUrl:'...',
    }
</script>
```

2.绑定class的几种方法

 （1）表达式为真，则加载css

```
        <div :class="{ 'active':isActive,'error':isError }"></div>

       <script>
        data:{
             isActive: true,
             isError:false,
        }
        </script>
```

 （2）使用computed

```
    <div :class="classes"></div>

    <script>
        computed:function(){
            return:{
                active:this.isActive,
            }
        }
    </script>
```

 (3)组件上使用



```
  <style>
        .article{
            color: red;
        }
        .active{
            color: black;
            font-size: 30px;
        }
    </style>

 <div id="app">
        <my-component :class="{ 'active': isActive }"></my-component>
    </div>>

<script>
    Vue.component('my-component',{
        template:'<p class="article">这是一个组件</p>'
    })
    var app=new Vue({
        el:'#app',
        data:{
            isActive:true
        }
    })
</script>
```

3.绑定内联样式

```
<div :style="styles">
            这是第二个组件
        </div>

  data:{
            isActive:true,
            styles:{
                color:'pink',
                fontSize: 35 +'px'
            }
        }
```



 

