---
title: Vue.js实战（4）
date: 2020-11-20 18:38:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


# Ch6

 

### 6.1 表单基本用法及常用小组件

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
        <p>汉语非即时显示</p>
        <textarea v-model="text" placeholder="输入"></textarea>
        <p>Content1:{{ text }}</p>
      
       <p>汉语即时显示</p>
        <input type="text" @input="handleInput" placeholder="输入2">
        <p>Content1:{{ text1 }}</p>

        <p>单选框</p>
        <!-- 单选框 -->
        <input type="radio" v-model="picked" value="HTML" id="html">
        <label for="html">HTML</label>
        <input type="radio" v-model="picked" value="JS" id="js">
        <label for="html">JavaScript</label>
        <input type="radio" v-model="picked" value="CSS" id="css">
        <label for="html">CSS</label>

        <span style="padding-left: 30px;">Picked:{{ picked }}</span>
        <br>
        <!-- 复选框 -->
        <p>复选框</p>
        <input type="checkbox" v-model="checked" id="checked" value="CSS">
        <label for="css">CSS</label>
        <input type="checkbox" v-model="checked" id="checked" value="JS">
        <label for="">JS</label>
        <input type="checkbox" v-model="checked" id="checked" value="HTML">
        <label for="html">HTML</label>
        <label for="checked">已选：{{ checked }}</label>

        <p>下拉框(单选)</p>
        <select v-model="selected">
            <option>HTML</option>
            <option>JS</option>
            <option>CSS</option>
        </select>
        <label for="selected">已选：{{ selected }}</label>

        <p>下拉框(多选)</p>
        <select v-model="selected1" multiple>
            <option>HTML</option>
            <option>JS</option>
            <option>CSS</option>
        </select>
        <label for="selected1">已选：{{ selected1 }}</label>


    </div>

    <script>
        var app=new Vue({
            el:"#app",
            data:{
                text:'',
                text1:'',
                picked:'false',
                checked:[''],
                selected:'',
                selected1:['']
            },
            computed:{

            },
            methods:{
                handleInput:function(e){
                    this.text1=e.target.value;
                }
            }
        })
    </script>
</body>
</html>
```

### 6.2 绑定值

选中显示a,未选中显示b

```html
        <p>复选框：</p>
        <input type="checkbox" v-model="picked2" :true-value="value1" :false-value="value2">
        <label>复选框：</label>
        <p>{{ picked2 }}</p>
        <p>Value1:{{ value1 }}</p>
        <p>Value2:{{ value2 }}</p>

```

### 6.3 修饰符

​	1 v-model.lazy 显示数据不是实时改变，回车或者失焦才会改变；

```html
      <p>.lazy</p>
        <input type="text" v-model.lazy="lazy">
        <p>Lazy:{{ lazy }}</p>
```

​	2 v-model.number 将输入类型转换为Number类型，否则虽然输入的是数字，其实类型是字符串；若是输入字符，不显示；

```html
        <p>.numebr</p>
        <input v-model.number="number">
        <p>number:{{ number }}</p>
```

​	3 v-model.trim 去除首尾空白；

```html
  <p>.trim</p>
        <input v-model.trim="trim">
        <p>trim:{{ trim }}</p> 
```

