# VUEX

> Vuex是一个专为Vuejs App开发的状态管理模式+库，采用集中式存储管理应用中的所有组件状态

## 一、简介

```js
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

这个状态自管理应用包含以下部分：

- 状态：驱动应用的数据源
- 视图：以声明方式将状态映射到视图
- 操作：响应在视图上用户输入导致的状态变化

![img](https://vuex.vuejs.org/flow.png)

当应用遇到多个组件共享状态时，单向数据流的简洁性容易被破坏：

- 多个视图依赖于同一状态
- 来自不同视图的行为需要改变同一状态

对于问题一，传参的方法对于多层嵌套的组件将会非常繁琐，并且对于兄弟组件间的状态传递无能为力。

对于问题二，我们经常会采用父子组件直接引用或者通过事件来变更和同步状态的多份拷贝。

以上的这些模式非常脆弱，通常会导致无法维护的代码。

```
总结：抽离出公用的状态
```

![vuex](https://vuex.vuejs.org/vuex.png)

如果您不打算开发大型单页应用，使用 Vuex 可能是繁琐冗余的。确实是如此——如果您的应用够简单，您最好不要使用 Vuex。一个简单的 [store 模式](https://v3.cn.vuejs.org/guide/state-management.html#从零打造简单状态管理)就足够您所需了。但是，如果您需要构建一个中大型单页应用，您很可能会考虑如何更好地在组件外部管理状态，Vuex 将会成为自然而然的选择。引用 Redux 的作者 Dan Abramov 的话说就是：

> Flux 架构就像眼镜：您自会知道什么时候需要它。



