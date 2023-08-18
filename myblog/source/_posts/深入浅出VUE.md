# 深入浅出 VUE.js

> 渐进式框架

## 一、Object 变化侦测

> ### 从状态生成 DOM，再输出到用户界面的一整套流程称作渲染，应用在运行时会不断重新渲染。响应式系统赋予框架重新渲染的能力，其中最重要的组成部分是变化侦测。

### 1.如何追踪变化？

> Object.defineProperty 和 ES6 的 Proxy

```js
function defineReactive(data, key, val) {
  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      return val
    },
    set: function (newVal) {
      if (val === newVal) {
        return
      }
      val = newVal
    },
  })
}
```

### 2.如何收集依赖？

> getter 中手机依赖，setter 中触发依赖

先收集依赖，然后属性发生变化时，将收集的依赖循环触发一遍

### 3.依赖收集在哪里？

> 收集到 Dep 中

```js
function defineReactive(data, key, val) {
  let dep = new Dep()
  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      dep.depend()
      return val
    },
    set: function (newVal) {
      val = newVal
      dep.notify()
    },
  })
}

export default class Dep {
  constructor() {
    this.subs = []
  }

  addSub(sub) {
    this.subs.push(sub)
  }

  removeSub(sub) {
    remove(sub)
  }

  depend() {
    if (window.target) {
      this.addSub(window.target)
    }
  }

  notify() {
    const subs = this.subs.slice()
    for (let i = 0, l = subs.length; i < l; i++) {
      subs[i].update()
    }
  }
}

function remove(arr, item) {
  if (arr.length) {
    const index = arr.indexOf(item)
    if (index > -1) {
      return arr.splice(index, 1)
    }
  }
}
```

### 4.依赖是谁？

> 收集 watcher

### 5.什么是 watcher？

```js
export default class Watcher {
  constructor(vm, expOrFn, cb) {
    this.vm = vm
    this.getter = parsePath(expOrFn)
    this.cb = cb
    this.val = this.getter()
  }

  get() {
    window.target = this
    let value = this.getter.call(this.vm, this.vm)
    window.target = undefined
    return value
  }

  update() {
    const oldValue = this.val
    this.val = this.get()
    this.cb.call(this.vm, this.val, oldValue)
  }
}
```

### 6.递归侦测所有 key

> 前面已经可以侦测某一个数据了，为了侦测所有数据，可以封装一个 Observer 类，作用是将一个数据内的所有属性转换成 getter/setter 的形式，然后追踪他们的变化

```js
export default class Observer {
  constructor(value) {
    this.value = value

    if (!Array.isArray(value)) {
      this.walk(value)
    }
  }

  //将一个正常的object转换为被侦测的object
  walk(obj) {
    const keys = Object.keys(obj)
    for (let i = 0; i < keys.length; i++) {
      defineReactive(obj, keys[i], obj[keys[i]])
    }
  }
}

function defineReactive(data, key, val) {
  if (typeof val === 'object') {
    new Observer(val)
  }

  let dep = new Dep()
  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      dep.depend()
      return val
    },
    set: function (newVal) {
      val = newVal
      dep.notify()
    },
  })
}
```

#### Object 的问题

> 数据的变化是通过 getter/setter 来追踪的，但是有些语法即使数据发生了变化，vue 也追踪不了变化。比如添加删除。
>
> vue 提供了 vm.$set和vm.$delete 来解决这个问题。

## 二、Array 变化侦测

#### 为什么 Array 和 Object 的侦测方式不同？

> object 的变化是靠 setter 来追踪，只要一个数据发生了变化就会触发 setter
>
> 但是数组会通过 push 等 array 方法来改变数组，并不会触发 getter/setter

### 1.如何追踪变化？

> 在用户使用 push 操作数组时得到通知，实现目的。
>
> 可惜在 ES6 之前，js 并没有提供元编程的能力，因此使用自定义的方法来覆盖原生的原型方法。
>
> 通过给 Array 添加拦截器，这样操作数据时执行的其实是拦截器中的方法，在拦截器中使用原生 Array 方法操作数组

### 2.拦截器

```js
const arrayProto = Array.prototype
export const arrayMethods = Object.create(arrayProto)
;['psuh', 'pop', 'shift', 'unshift', 'splice', 'sort', 'reverse'].forEach(
  function (method) {
    const original = arrayProto[method]
    Object.defineProperty(arrayMethods, method, {
      value: function (...args) {
        return original.apply(this, args)
      },
      enumerable: false,
      writable: true,
      configurable: true,
    })
  }
)
```

### 3.使用拦截器覆盖 Array 原型

> 有了拦截器，不可覆盖 Array.prototype,会污染全局 Array。
>
> 因此，通过 observer 将数据转换为响应式的。

```js
export class Observer {
  constructor(value) {
    this.value = value

    if (Array.isArray(value)) {
      value.__proto__ = arrayMethods
    } else {
      this.walk(value)
    }
  }
}
```

### 4.将拦截器方法挂载到数组的属性上

> 如果不能使用_proto_就直接将arrayMethods身上的方法设置到被侦测的数组上

### 5.如何收集数组依赖？

```js
{
	list:[1,2,3,4,5]	
}
```

> 其实不管value是什么，只要是object的某个属性的数据，肯定通过key来读取数据，这就会触发getter

```js
import { Observer } from "./ArrayObserver"

function defineReactive (data, key, val) {
  if (typeof val === 'object') new Observer(val)
  let dep = new Dep()
  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      dep.depend()
      return val
    },
    set: function (newVal) {
      if (val === newVal) {
        return
      }
      dep.notify()
      val = newVal
    }
  })
}
```

#### 收集依赖

```js

```



# 虚拟DOM

## 五、虚拟DOM

> Vue，Aug，RT都是声明式操作DOM

为了把状态渲染在DOM上，有时需要更新DOM，最简单的方法，删除所有DOM重新生成一个DOM。

代价昂贵->仅仅删除需要的DOM

- Angular使用脏检查
- React使用虚拟DOM
- Vue细粒度绑定

虚拟DOM的方式是通过状态生成一个虚拟节点树，使用虚拟节点渲染树，渲染之前会使用新生成的虚拟节点树和上一次生成的虚拟节点数进行比对，只渲染不同的部分。

### 1.为什么引入虚拟DOM？

Angular和React的变化侦测有一个共同点，他们不知道那些状态更新，因此进行暴力比对。

VUE一定程度上知道那些状态发生变化。代价是粒度太细每一个绑定都会有一个watcher来观察状态变化，会有内存开销。

VUE2使用组件级别的watcher实例，状态发生变化时仅仅通知到组件，然后组件内部进行虚拟DOM对比和渲染。

### 2.虚拟DOM比对算法Patch



## 六、VNODE

### 1.什么是vnode？

> vuejs中存在一个vnode类，可以实例化不同类型的vnode实例，不同类型的实例表示不同类型的dom元素。
>
> 本质上是一个JS普通的对象，是从VNode类实例化的对象。

### 2.VNode的作用

- 每次渲染视图时都是先创建vnode，然后用它创建真实DOM插入到页面中，所以可以将上次渲染的vnode缓存起来，下次渲染可以进行比对。
- vue目前使用中等颗粒度，当状态发生变化时，只通知到组件及别，然后组件内使用虚拟DOM渲染视图
- 以组件为单位进行重新渲染。

### 3.VNode类型

- 注释
- 文本
- 元素
- 组件
- 函数式组件
- 克隆节点：将现有节点属性赋值到新节点，作用是优化静态节点和插槽节点，用于复制不需要重新传染的node

## 七、patch

> 虚拟DOM最核心的就是patcj，可以将vnode渲染成真实DOM
>
> Ptach也可以叫做patching算法，通过它渲染真实DOM，是通过对比结果找出需要更新的DOM
>
> DOM操作的执行速度远不如JS的运算速度快，因此把大量的DOM操作搬运到JS中，使用patching来计算出真正需要更新的节点，最大幅度减少DOM操作，从而显著提升性能。

### 1. patch介绍

对DOM修改需要三件事：

- 创建新增节点
- 删除已经废弃的节点
- 修改需要更新的节点

#### 新增节点

- 首次加载时，不存在oldVNode，因此使用新的vnode
- 新旧节点不同时，使用新vnode替换

#### 删除节点

- 新的vnode不存在的结点都删除
- 当新vnode和旧vnode完全不是一个节点时，先插入再删除

#### 更新结点

- 当新旧两个结点是相同结点时，需要进行更细致的对比，然后对oldVnode在视图中对应的真实结点进行更新。

#### 创建节点

事实上，只有三种类型的节点会被创建并插入到DOM中，元素节点、注释节点、和文本节点；

- 判断vnode是否为元素节点，只需要判断有无tag属性即可。调用createElement方法来创建真实元素节点。最后插入指定父节点。
- 将元素渲染到视图：调用parentNode.appendChild()方法即可。再插入新节点的子结点。
- 注释节点有唯一的标识属性`isCOmment`



### 2删除节点

```js
function removeVnodes (vnodes, startIdx, endIdx) {
  for (; startIdx <= endIdx; ++startIdx) {
    const ch = vnodes[startIdx]
    if (isDef(ch)) {
      removeVnode(ch.elm)
    }
  }
}

const nodeOps = {
  removeChild (node, child) {
    node.removeChild(child)
  }
}

function removeVnode (el) {
  const parent = nodeOps.parentNode(el)
  if (isDef(parent)) {
    nodeOps.removeChild(parent, el)
  }
}
```

##### 为什么不直接使用parent.removeChild(child)删除节点而是封装成函数放在nodeOps中？

> 涉及到跨平台渲染的知识，阿里的Weex可以使用相同的组件模型为iOS和Andriod编写原生渲染的应用。
>
> 而跨平台渲染的本质时在设计框架时，让框架的渲染机制和DOM解耦，只要把框架更新DOM的节点操作进行封装时，就可以实现跨平台渲染。

### 3.更新节点

- 静态节点

如果新旧节点是静态节点，则不需要进行更新，直接跳过更新节点的过程。

静态节点就是：一旦渲染到界面就不会随状态发生变化

- 新虚拟节点有文本属性

如果新生成的vnode有text属性，那么不管之前旧节点的子节点是什么，直接调用setTextContent方法来将视图中DOM节点内容更改为虚拟节点所保存的文字

- 新虚拟节点无文本属性

无text属性，则为元素节点

> 有children，需要比对
>
> 无children，删除就完事了

### 4.更新子结点



# 模板编译原理

> 模板给与了很大的能力
>
> vue创建HTML除了模板，还有手动写渲染函数来创建，使用jsx来创建HTML

## 八、模板编译

![](https://s3.bmp.ovh/imgs/2023/08/18/3209f200cf5fb938.png)

> vuejs提供了模板语法，允许声明式描述状态和DOM之间的绑定关系。

### 1.概念















































































































