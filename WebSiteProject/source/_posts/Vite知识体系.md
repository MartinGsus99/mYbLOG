---
title: Vite知识体系
date: 2023-03-27 18:51:45
categories: 
    - 前端
tags: 
    - 项目构建
    - 笔记
mp3: 
cover: img/bg3.jpg
---


# Vite知识体系

## 一、浅谈构建工具

### 1. Why we need build tools?

- 模块化（ESM、CommonJS、UMD）
- 资源编译（高级语法的编译）
- 产物质量（代码提及、代码性能）
- 开发效率（热更新）

### 2.构建工具的意义

- 提供模块加载方案、兼容不同的模块规范；
- 高级语法转义（Sass，TS）、资源加载如图片、字体、worker；
- 产物压缩、无用代码删除、语法降级；
- 热更新；

### 3.Vite是什么？Why vite？

##### 组成：

- No-bundle开发服务、源文件无需打包；
- 生产环境基于Rollup的Bundler；

##### 核心特征：

- 高性能，dev启动速度和热更新速度非常快；
- 简单易用，开发者体验好；

### 4.当下问题

##### 问题

- 缓慢启动；
- 缓慢的热更新；

##### 瓶颈

- bundle带来的性能开销；
- JS语言的性能瓶颈；

##### 行业趋势

- 全球浏览器对原生ESM的普遍支持；

```
1.script标签增加type=“module”属性；
2.使用ESM模块导入导出语法；
```

![](https://s3.bmp.ovh/imgs/2023/02/09/954d53ed35dab73a.jpg)

- 基于原生语言（Go、Rust）编写前端编译工具链；

![](https://s3.bmp.ovh/imgs/2023/02/09/a162a7181e2b1488.jpg)



## 二、Vite概要

### 1.内置Web构建功能

![](https://s3.bmp.ovh/imgs/2023/02/09/b6130def732894e1.jpg)

![](https://s3.bmp.ovh/imgs/2023/02/09/5766272cb741272e.jpg)

## 三、Vite上手

### 1.项目初始化

```shell
# 提前安装pnpm
npm i -g pnpm

# 初始化命令
pnpm create vite

#安装依赖
pnpm install

#启动项目
npm run dev

#安装sass
pnpm install sass -D

#打包
tsc && vite build

```

```tsx
import * as React from 'react';
import { Component } from 'react';
import styles from './index.module.scss';

export function Header(){
    return (
        <div><h1 className={styles.header}>Header</h1></div>
    )
}
```

```scss
.header{
    color:red;
}
```

### 2.无需额外配置

> 可以保存组件状态：修改A组件代码时，Web热更新之后，不会影响其他组件的状态；

### 3.Tree Shaking

##### 原理

- 基于ESM的import/export语句依赖关系，与实时状态无关；
- 在构建阶段将未使用到的代码进行删除；
- Tree shaking 在vite中无需配置，默认开启；

### 4.优点

- 响应迅速
- 开箱即用

## 四、Vite整体架构

![](https://s3.bmp.ovh/imgs/2023/02/09/9290159fce29e6d4.jpg)

### 1.单文件编译

> 使用Esbuild编译TS/TSX；
>
> 预打包：扫描代码进行预先打包；

##### 优势

- 编译速度提升10-100X

##### 缺点

- 不支持类型检查；（运行之前需要调用`tsc`）
- 不支持语法降级到ES5；

### 2.代码压缩

> Esbuild作为默认压缩工具，替换传统的Terser、Uglify.js等压缩工具；

### 3.插件机制

- 开发环境：模拟roolup插件机制
- 生产环境：直接使用rollup

## 五、Vite进阶路线

### 1.深入双引擎

- esbuild
- rollupJS

##### 学习

- 查看官方文档
- 先了解基本使用，动手尝试各项常用配置；
- 学习其插件开发；

### 2.插件机制

- 易于抽离核心逻辑
- 易于拓展

![](https://s3.bmp.ovh/imgs/2023/02/09/8ef80e5113384463.jpg)

- config
- resolveId
- load
- tranform

![](https://s3.bmp.ovh/imgs/2023/02/09/ad4af8b0fc78d654.jpg)

### 3.学习

- Vite插件开发文档；
- 学习其他插件实现，json加载等；

### 4.拆包（代码分割）

![](https://s3.bmp.ovh/imgs/2023/02/09/62c96b5942f5b559.jpg)

### 5.JS编译工具（Babel）

源代码->AST->AST->降级代码

- AST为抽象语法树；

### 6.语法安全降级

![](https://s3.bmp.ovh/imgs/2023/02/09/7bd9f45a3245d6e7.jpg)

- 上层解决方案：plugin-legacy
- 底层原理：借助babel实现；提前注入polyfill；

### 7.服务端渲染（SSR）

- 提升首屏性能
- SEO优化；

![](https://s3.bmp.ovh/imgs/2023/02/09/c849fc3dd53d12c8.jpg)

### 8.深入理解底层标准

![](https://s3.bmp.ovh/imgs/2023/02/09/5a034d64573a380a.jpg)

