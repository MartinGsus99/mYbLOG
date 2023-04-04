---
title: CSS笔记
date: 2020-12-3 21:18:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/welcome-cover2.jpg
---


1.向 div 元素添加阴影

box-shadow: 20px 10px 5px pink;

参数：长 宽 颜色

2.display

| none         | 此元素不会被显示。                                   |
| ------------ | ---------------------------------------------------- |
| block        | 此元素将显示为块级元素，此元素前后会带有换行符。     |
| inline       | 默认。此元素会被显示为内联元素，元素前后没有换行符。 |
| inline-block | 行内块元素。（CSS2.1 新增的值）                      |

3.border-redius

给div元素添加圆角的边框

4.outline

设置元素周围的轮廓

| 值              | 描述                                                         |
| :-------------- | :----------------------------------------------------------- |
| *outline-color* | 规定边框的颜色。参阅：[outline-color](https://www.runoob.com/cssref/pr-outline-color.html) 中可能的值。 |
| *outline-style* | 规定边框的样式。参阅：[outline-style](https://www.runoob.com/cssref/pr-outline-style.html) 中可能的值。 |
| *outline-width* | 规定边框的宽度。参阅：[outline-width](https://www.runoob.com/cssref/pr-outline-width.html) 中可能的值。 |
| inherit         | 规定应该从父元素继承 outline 属性的设置。                    |

5.a:active 激活后样式
{
background-color:yellow;
}