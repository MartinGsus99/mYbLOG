---
title: WebGL
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - 可视化
    - 笔记
mp3: 
cover: img/bg2.jpg
---


# WebGL

## 一、Why WebGL？Why GPU？

```
GPU!=WebGL!=3D
```

### 1.现代图形系统

- 光栅（Raster）：几乎所有的现代图形系统都是基于光栅来绘制图形的，光栅就是指构成图像的像素阵列；
- 像素：一个像素对应图像的一个带你，通常保存图像的某个具体位置的颜色信息等；
- 帧缓存（Frame Buffer）：绘图过程中，像素信息存放在帧缓存中，是一块内存地址；

##### 具体步骤

- 轮廓提取/ meshing
- 光栅化
- 帧缓存
- 渲染

![](https://s3.bmp.ovh/imgs/2023/02/14/57143b0a02e56c3d.jpg)


$$
Data->Processor->Frame Buffer->Pixel
$$
GPU由大量小的运算单元构成，每个运算单元只负责很简单的计算；计算单元相互独立，因此可以并行计算；

### 2.WebGL

$$
OpenGL----js接口---->WebGL
$$

##### WebGL代码流程

- 创建WebGL上下文
- 创建WebGL Program
- 将数据存入缓冲区
- 将缓冲区数据读取到GPU
- GPU执行WebGL程序，输出结果

![](https://s3.bmp.ovh/imgs/2023/02/14/204b3600bac6924e.jpg)

```js
//define shaders

//create program

//set points
//中心点是坐标原点（0，0）

//create & build Buffer

//Frame Buffer to GPU

//output
```









