---
title: Vue.js实战（6）
date: 2020-12-1 21:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


# Ch8 自定义命令

### 一、基本用法

```javascript
//全局注册

    Vue.directive('focus',{
            //指令选项
        })
//局部注册，作用域在app内
        var app=new Vue({
            el:"#app",
            directives:{
                focus:{
                    //指令选项
                }
            }
        })
```

1. bind：第一次绑定到元素时使用；
2. inserted：被绑定元素插入父节点时使用；
3. update：绑定元素模板更新时使用，不论绑定值是否发生变化；
4. componentUpdated：被绑定元素完成一次更新周期时使用；
5. unbind： 指令与元素解绑时调用；

### 二、实战

代码已经存在电脑



# Ch9 Render函数

### 一、Virtual Dom：一个JavaScript对象，在状态发生变化时，Virtual Dom会进行Diff运算，来更新需要被替换的DOM，并不是全部重新绘制；

```javascript
var vNode={
    tag:'div',
    attributes:{
        id:'main'
    },
    children:[
        //p节点
    ]
}
```

1.vNode分类：

| Node           | Function         |
| -------------- | ---------------- |
| ElementVnode   | 普通元素节点     |
| TextVNode      | 文本节点         |
| ComponentVNode | 组件节点         |
| EmptyVNode     | 无内容的注释节点 |
| CloneVNode     | 克隆节点         |

### 二、createElement用法

1.传统方法：

```html
    <div id="app">
        <ele></ele>

    </div>

    <script>
        Vue.component('ele', {
            template: ' <div id="element" :class="{show:show}" @click="handleClick">元素内容</div>',
            data: function () {
                return {
                    show: true
                }
            },
            methods: {
                handleClick: function () {
                    console.log('clock');
                }
            }
        });

        var app = new Vue({
            el: "#app",
        })
    </script>
```

2.使用Render改写后

```html
    <div id="app">
        <ele></ele>
    </div>

    <script>
        Vue.component('ele', {
            render: function (createElement) {
                return createElement(
                    'div',
                    {
                        class: {
                            'show': this.show
                        },
                        attrs: {
                            id: 'element'
                        },
                        on: {
                            click: this.handleClick
                        }
                    },
                    '文本内容1'
                )
            },
            data: function () {
                return { show: true }
            },
            methods: {
                handleClick: function () {
                    console.log('click');
                }
            }
        });

        var app = new Vue({
            el: "#app",
        })
    </script>
```

3，就此例而言，render得写法复杂于template写法，所以在合适的场景使用render

4.约束：所有的组件树中，如果VNODE是组件或者含有slot，那么Vnode必须唯一

5.render函数里创建了一个cloneVNode得工厂函数，通过递归将slot所有子节点克隆一份，并对VNode的关键属性也复制了一份；

### 三、函数化组件

​	1.vue提供了一个functional的布尔值选项，设置为true可以使组件无状态和无实例，也就没有data和this上下文；render返回虚拟节点也更加容易渲染；

​	2.函数化组件得是适用场景：

- 程序化得在多个组件中选择一个
- 在将children，props，data传递给子组件之前操作他们；