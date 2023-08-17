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



























































