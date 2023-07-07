---
title: 防抖与节流
date: 2023-07-06 13:51:45
categories:
  - JS
tags:
  - JS
  - JS技巧
mp3:
cover: img/bg2.jpg
---

# 防抖与节流

## 一、防抖

### 1.应用场景

- 窗口 resize，滚动条 scroll，输入框 input
- 持续发生，具有过程的事件

### 2.应用：利用闭包实现

```js
let inputEvent = document.querySelector('input')
let content = document.getElementById('value')

function inputChange() {
  console.log(this.value)
  content.innerHTML = inputEvent.value
}

//使用闭包形成防抖
//闭包：函数里有一个内部函数，并返回出去，还是用了外部函数的变量
inputEvent.oninput = debounce(inputChange, 1000)
function debounce(func, delay) {
  let timer = null
  return function () {
    //如果定时器不空，则清除之前的timer
    if (timer !== null) {
      clearTimeout(timer)
    }
    timer = setTimeout(() => {
      func.call(this)
    }, delay)
  }
}
```

## 二、节流

### 1.应用场景

- 在规定的时间里执行一次操作，但是不一定只执行一次

```js
function alertAdv() {
  alert('广告')
}

window.onscroll = ttrottle(alertAdv, 1000)

function ttrottle(fn, delay) {
  let timer = true
  return function () {
    if (timer) {
      setTimeout(() => {
        fn.call(this)
        timer = true
      }, delay)
    }
    timer = false
  }
}
```
