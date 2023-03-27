---
title: Vuex
date: 2023-03-27 15:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
mp3: 
cover: img/vue.png
---


# Vuex

## 一、基础概念

#### 1.Vuex是什么？

状态管理模式+库；采用集中式存储管理应用组件的状态，并以相应的规则保证状态以一种可预测的方式发生变化。

#### 2.状态管理模式

举个栗子🌰

```vue
const Counter = {
  // 状态
  data () {
    return {
      count: 0
    }
  },
  // 视图
  template: `
    <div>{{ count }}</div>
  `,
  // 操作
  methods: {
    increment () {
      this.count++
    }
  }
}

createApp(Counter).mount('#app')
```

该APP包含以下部分：

- 状态，驱动应用的数据源；
- 视图，以声明方式将状态映射到试图；
- 操作，响应在视图上的用户输入导致状态变化；

![](https://s3.bmp.ovh/imgs/2022/10/29/d3e085834c6b02a0.png)

- 存在一种多个视图依赖于同一种状态的情况；
- 不同视图变更统一状态的情况；

##### 思路

把组件的共享状态抽取出来，以一个全局单例模式管理；

通过定义和隔离状态管理中的各种概念并通过强制规则维持视图和状态间的独立性，我们的代码将会变得更结构化且更易于维护；

![](https://s3.bmp.ovh/imgs/2022/10/29/348dbed9d3ef8569.png)

#### 3.安装方法

```html
<script src="/path/to/vue.js"></script>
<script src="/path/to/vuex.js"></script>
```

```sh
npm install vuex@next --save
```

#### 4. store基础

如果有一部分的状态需要在多个组件实例间共享，可以使用reactive()来创建一个响应式对象，并将它导入到多个组件中。

```js
//store.js
import { reactive } from 'vue';

export const store=reactive({
    count:0
})
```

```vue
//componentA
<script>
	import { store } from './store.js'
    
    export default {
        data(){
            return{
                store,
            }
        }
    }
</script>

<template>
From A:{{ store.count }}
</template>
```

```vue
//componentB
<script>
	import { store } from './store.js'
    
    export default {
        data(){
            return{
                store,
            }
        }
    }
</script>

<template>
From B:{{ store.count }}
</template>
```

现在，所有引入了store的组件都可以改动count，但是从长远看这种代码是不容易维护的。

解决方法：在store上定义方法，方法的名字需要能表达意图；

```js
//store.js
import { reactive } from 'vue';

export const store=reactive({
    count:0，
    increment(){
    	this.count++
	},
})
```

```vue
<template>
  <button @click="store.increment()">
    From B: {{ store.count }}
  </button>
</template>
```

#### 4.SSR（Server-Side Rendering）服务端渲染

> 默认情况下，Vue 组件的职责是在浏览器中生成和操作 DOM。然而，Vue 也支持将组件在服务端直接渲染成 HTML 字符串，作为服务端响应返回给浏览器，最后在浏览器端将静态的 HTML“激活”(hydrate) 为能够交互的客户端应用。 

##### 优点

- 更快的首屏加载：服务端渲染的 HTML 无需等到所有的 JavaScript 都下载并执行完成之后才显示，所以你的用户将会更快地看到完整渲染的页面。数据获取过程在首次访问时在服务端完成，相比于从客户端获取，可能有更快的数据库连接。
- 统一的心智模型
- 更好的SEO：搜索引擎爬虫可以直接看到完全渲染的页面。

## 二、使用

### 1.最简单的store

```js
import { createApp } from 'vue'
import { createStore } from 'vuex'

// 创建一个新的 store 实例
const store = createStore({
  state () {
    return {
      count: 0
    }
  },
  mutations: {
    increment (state) {
      state.count++
    }
  }
})

const app = createApp({ /* 根组件 */ })

// 将 store 实例作为插件安装
app.use(store)
```





