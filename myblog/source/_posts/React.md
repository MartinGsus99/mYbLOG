---
title: React
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - React
    - 笔记
mp3: 
cover: img/bg4.jpeg
---


# React

## 一、应用

- 前端应用
- 移动原生
- 桌面应用Electron  React 3D

## 二、原型

1. Facebook在其php生态中引入了组合式组件的思想，启发了后来的react设计
2. J.W创建了FaxJS,也就是React的原型；
3. Facebook收购ins后，该项目在内使用，基于FaxJS创建了React；

## 三、React设计思路

### 1.UI编程痛点

- 状态更新，UI不会自动更新，需要手动调用DOM
- 欠缺基本的代码层面的封装和隔离，代码层面没有组件化
- UI之间的数据依赖关系需要手动维护，如果 依赖链条过长，会遇到“Callbace Hell”

### 2.响应式与转换式

- 转换式：给定输入求解输出；  （编译器、数值计算）
- 响应式：监听事件没消息驱动； （监控系统、UI界面）

```
事件->执行既定的回调->状态更新->UI更新
```

### 3.响应式编程

- 状态更新，UI自动更新
- 前端代码组件化、可复用、可封装
- 状态之间的互相依赖关系、只需要声明计科

### 4.组件化

- 组件是组件的组合/原子组件
- 组件内部拥有状态，外部不可见
- 父组件可将状态传入组件内部

### 5.状态归属问题

```
Note：共享变量需要提升到最近的祖先组件、可以用状态管理解决；
E.g:如果状态归属于两个节点，就向上寻找到最近的祖宗节点；
```

![](https://s3.bmp.ovh/imgs/2023/01/30/edd9edf1a3d14f27.jpg)

> Javascript中、函数是【一等公民】
>
> **通过向子组件传递function来改变根组件的变量（形成双向数据流）

### 6.思考

- React是单向数据流、还是双向数据流？

> 其实是单向数据流，永远是父组件给子组件传递，并不代表子组件不能改变父组件数据；

- 如何解决状态不合理上升的问题？（第五节解决）

> 状态管理库

- 组件的状态改变之后，如何更新DOM？（第四节解决）

> 1

### 7.组件设计

- 组件声明了状态和UI的映射；
- 组件拥有Props/State两种状态；
- 组件可由其他组件拼装而成；

解法：

- 组件内部拥有私有状态State
- 组件接受外部的Props状态提供复用性
- 根据当前的state/props返回一个UI

```react
function Component(props){
    const {url}=props;
    this.text='click me';
    
    return(
    	<div>
        	<SubComponent props={{color:'red'}}></SubComponent>
            <img src={url}></img>
            <button>clike me</button>
        </div>
    )
}
```

### 8.生命周期

![](https://s3.bmp.ovh/imgs/2023/01/30/4fc6e86cf176a88b.jpg)

### 9.React Hooks 

```react
import React,{useState} from 'react';

function Example(){
    //声明一个新状态需要手动调用useState，返回一个状态和set该状态的函数；
    const [count,setState]=useState(0);
    
    //传入一个函数和一个数组秘书组是状态的数组，称作依赖项，该函数在mount时执行
    //有“副作用”的函数，要传入useEffect来执行。副作用代表出来单纯的计算之外还要做其他事情。比如网络请求，更新DOM，localStorage存储数据等；
    useEffect(()=>{
        document.title=`You clicked ${count} times`;
    })
    
    return(
    	<div>
        	<p>Clicked { count } times</p>
            <button onClick={()=>setCount(count+1)}>Click +1</button>
        </div>
    )
}
```

### Hook使用法则

- 不要在循环、条件或嵌套中调用hook

## 四、React实现

### 1.Problems

- JSX不符合JS语法标准；

![](https://s3.bmp.ovh/imgs/2023/01/30/1fc630e94d6d6c60.jpg)

- 返回的JSX发生改变时，如何更新DOM；

> 计算新旧JSX的Difference

- 指令式：说一步做一步
- 声明式
- 响应式

![](https://s3.bmp.ovh/imgs/2023/01/30/9ff90ed31b0de3e3.jpg)

![](https://s3.bmp.ovh/imgs/2023/01/30/cf361645d5820a2d.jpg)

```
state改变->计算diff->更新dom

How to diff?

更新次数少<----tradeoff---->计算速度快
完美的最小Diff算法，需要O(n^3)
换取时间，需要O（n）
```

|       元素       | 更新方法 |
| :--------------: | :------: |
|   不同类型元素   |   替换   |
| 同类型的DOM元素  |   更新   |
| 同类型的组件元素 |   递归   |

弊病：最顶层的父组件状态发生改变，子组件全部更新

- state/props改变时，如何重新触发render函数；

## 五、React状态管理库

### 1.核心思想

> ***将状态抽离到UI外部进行统一管理
>
> 只存放需要共享的、距离较远的

### 2.常用管理库推荐

- redux
- xstate
- mobx
- recoil

### 3.状态机

> 当前状态，收到外部事件，迁移到下一个状态

### 4.ModernJS/Reduck

## 六、应用级框架科普

- NextJS  (研究一下Vercel)
- ModernJS (Web Infra)全栈开发框架
- Blitz 无API思想的全栈开发框架，开发过程无需写API调用与CRUD逻辑 



























