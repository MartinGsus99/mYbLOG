---
title: Vue.js实战（5）
date: 2020-11-27 21:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---

# Ch7 组件详解

### 1.组件的创建使用

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
        <my-component1></my-component1>
    </div>

    <script>

        Vue.component('my-component1',{
            template:'<div><p>This is my component1</p></div>'
        });


        var app=new Vue({
            el:"#app",
        });
    </script>
</body>
</html>
```

注意： a.组件需要注册之后才可以使用；	b.组件template中必须被一个元素包含，如\<div>\</div>

​		   c.组件可以使用data,methods,computed; data必须是函数，然后return；

### 2.组件数据的使用

三个组件都能实现自增,但是数据互不影响

```html
 <div id="app">
        <my-component2></my-component2>
        <my-component2></my-component2>
        <my-component2></my-component2>
    </div>
    
      Vue.component('my-component2',{
            template:'<div>       <p>Counter:</p><p>{{ count }}</p><button type="button" @click="count++">+1</button></div>',
            data:function(){
                return{
                    count:0
                } 
            }
        });
```

3. ### 使用props传递数据

   ​	1.组件除了复用以外，更重要的是组件之间的通信；props中声明的数据与组件data函数return的数据主要区别是props的来自父级，而data中的组件是自己的数据，作用域是组件本身；这两种数据都可以在template、computed和methods中使用；
   
   ```html
    <my-component3 message="来自父组件的数据！！"></my-component3>
    
    
           Vue.component('my-component3', {
               props: ['message'],
               template: '<div>{{ message }}</div>'
           });
   ```
   
   ​	2.小细节

```
  <my-component2 message="[1,2,3]"></my-component2>   //messgae.length=7
  <my-component2 :message="[1,2,3]"></my-component2>	//messgae.length=3 数组长度
```

​		 3.单向数据流：父级->子级，解耦，避免子级操作父级数据；若props作为需要抓变得原始值，可以用计算属性；

​		 4.数据验证

```javascript
  Vue.component('data-validator',{
            props:{
                propA:Number,
                propB:[String,Number],
                propC:{
                    type:Boolean,
                    default:true
                },
                propD:{
                    type:Number,
                    required:true
                },
                propE:{
                    type:Array,
                    dafault:function(){
                        return [];
                    },
                //自定义验证器
                propF:{
                    validator:function(value){
                        return value>10;
                    }
                }
                }
            }
        });
```

4.组件通信

​	1.自定义事件：子组件向父组件传递数据

​	2.双向绑定的v-model组件需要满足下面两个要求：

​				*接受一个value属性

  			 *在有新的value前出发input事件

​	3.使用中央时间总线Bus实现父子，兄弟，跨级的组件间通信

​	4.父链 this.$parent   this.$children  尽管Vue允许这样的操作，业务中，子组件应该尽可能避免以来父组件的数据（解耦？？）建议使用props和$emit

​	5.子组件索引：通过$refs来获取子组件实现（注意：$refs只在组件渲染完成之后才填充，并且他是非响应式的。仅仅作为一个应急方案，应当避免再模板和计算属性中使用$refs）

### 4.使用slot分发内容

当需要让组件组合使用，混合父组件的内容和子组件的模板时，用到slot，成为内容分发；

props传递数据，events触发事件，slot内容分发构成了Vue组建的3个API来源；

​	1.作用域

```html
<child-component>
	{{ message }}  //绑定父组件的数据
</child-component>


<child-component v-show="showMe"></child-component> //绑定的是父组件

var app=new Vue({
    el:"#app",
    data:{
    showMe: True;
}
});

<child-component v-show="showMe"></child-component> //绑定的是子组件

Vue.component('child-component',{
template:'<div v-show="showMe"></div>',
data:function(){
	retunr {
			showMe:True
}
}
})

```

​	2.slot用法

​				单个slot

```html
 <div id="app">
        <child-component></child-component>

        <child-component>
            <p>Car~~</p>
    </child-component>
    </div>
    <script>
        Vue.component('child-component', {
            template: "\
            <div>\
                <slot>\
                    <p>您的购物车空空如也！</p>\
                </slot>\
            </div>",

        });

        var app = new Vue({
            el: "#app",
        })
    </script>
```

​				具名slot和单个slot混用

```html
<div id="app">
        <child-component>
            <h2 slot="header">此去经年</h2>
            <p>从前车马很慢，书信很慢，一生只够爱一个人。</p>
            <div slot="footer">Writted By GuiGui</div>
        </child-component>
    </div>

    <script>
        Vue.component('child-component', {
            template: '\
            <div class="container">\
                <div class="header">\
                    <slot name="header"></slot>\
                </div>\
                <div class="main">\
                    <slot></slot>\
                </div>\
                <div class="footer">\
                    <slot name="footer"></slot>\
                </div>\
            </div>',
        });

```

​	3.作用域插槽：使用一个可复用的模板替代已渲染元素。？？？

​	4.访问slot：this.$slot.name;

### 5.组件高级用法

​	1.递归组件：组件在他的模板内递归调用自己，只要给组件设置name即可；可以用于开发具未知层级关系的独立组件；

​	注：必须设置一个条件来限制递归数量，否则抛出错误：max stack size exceeded;

​	2.内联模板：给组件标签使用inline-template特性，组件会把它的内容当作模板；

​	3.动态组件：vue.js提供了一个特殊元素\<component>用来挂载不同的组件，使用is特性来选择需要挂载的组件

```html
 <div id="app">
        <component :is="currentChoose"></component>
        <button @click="handleChangeView('A')">红灯</button>
        <button @click="handleChangeView('B')">黄灯</button>
        <button @click="handleChangeView('C')">绿灯</button>
    </div>

 
    <script>



        var app = new Vue({
            el: "#app",
            components:{
                comA:{
                    template:'<div style="color: red;">A组件</div>'
                },
                comB:{
                    template:'<div style="color: yellow;">B组件</div>'
                },
                comC:{
                    template:'<div style="color: green;">C组件</div>'
                },
            },
            data: {
                currentChoose:'comA',
            },
            methods: {
                handleChangeView:function(component){
                    this.currentChoose='com'+component;
                },
            },
        })
    </script>
```

​	4.异步组件：仅仅加载需要的组件，提高性能；（vue允许将组件定义为一个工厂函数，动态的解析组件，只在组件需要渲染时触发工厂函数，并且将结果缓存，用于再次渲染）

### 6其他

​	1.$nextTick 异步更新队列：vue仅仅会绘制最后一次改变，英雌因此当showtext=true的时候，其实还没有创建这个div，需要等到下一次刷新；

```html
 <div id="app">
        <div id="div" v-if="showText">This is show me text;</div>
        <button @click="showMeText">点击显示文本</button>
    </div>


    <script>



        var app = new Vue({
            el: "#app",
            data: {
                showText: false
            },
            methods: {
                showMeText: function () {
                    this.showText = true;
                    this.$nextTick(function(){
                        var text=document.getElementById('div').innerHTML;
                        console.log(text);
                    });
                }
            }
        })
    </script>
```

​	2.手动挂载实例$mount