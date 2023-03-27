# JS

## 一、各司其职

> HTML、CSS、JS职能分离

![](https://s3.bmp.ovh/imgs/2023/01/17/f3f6568ed1415a07.jpg)



## 二、组件封装

> 好的UI组件具有正确性、拓展性、复用性

### 1.结构

轮播图其实是一个列表结构；

通过css将图片层叠在一起；

### 2.展现效果

### 3.行为

API 功能

Event 控制流：使用自定义的事件来解耦

### 4.改进空间

- 解耦+





## 三、过程抽象

> 应用函数时编程思想

- 用来处理局部细节控制的方法
- 函数式编程思想的基础应用

1.once

一个方法设置了timewaite以后，如果在time内多次激活方法会报错，这个时候需要用once方法来禁止多次调用。

```js
buttons.forEach((button)=>{
    button.addEventListener('click',once((evt)=>{
        const target=evt.target;
        setTimeout(()=>{
            list.removeChild(target);
        },2000)				//设置2000ms
    })，{once:true})；		//仅允许调用一次；
})；
```

```js
//once function的实现

function once(fn){
    //外部闭包
    return function(...args){
        //内部闭包
        if(fn){
            const ret=fn.apply(this,args);
            fn=null;
            return ret;
        }
    }
}
```

为了能够让”只执行一次“的需求覆盖不同的事件处理，我们可以将这个需求剥离出来。这个过程，我们成为**过程抽象**

















