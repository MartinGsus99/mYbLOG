---
title: Vue笔记
date: 2020-11-12 2:51:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
mp3: 
cover: img/vue.png
---

# VUE错误笔记

1.Component template should contain exactly one root element. If you are using v-if on multiple element

解决方法：每个 Component只能有一个<div></div>div>，所有的代码需要放进这个div中。

2.错误缩进

解决方案：关闭缩进报错工具。





# VUE备忘笔记

1.Computed Properties与普通方法的区别

computed properties 会把结果“缓存”起来，每次调用对应的Computed Properties如果所依赖的数据没有变动，则使用已经计算好的值；

2.watch表示监听方法

可以监控vue对象中数据的变换；

3.两者比较：

```javascript
  watch:{
                city:function(city_name){
                    this.full_address=city_name+'-'+this.street;
                },
                street:function(street_name){
                    this.full_address=this.city+'-'+street_name;
                }
            },
            computed:{
                full_address1:function(){
                    return full_address1=this.city+' '+this.street
                }
```

4.component命名规则：小写字母+横线

例子：

```vue
Vue.component('my-component-name', { /*....*/})
```

W3C规范：

```vue
Vue.component('MyComponentName', { /*....*/})
```

可以使用\<MyConponentName\/>调用；