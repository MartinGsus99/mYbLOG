---
title: Web Audio API
date: 2023-06-26 21:13:45
categories:
  - 前端
tags:
  - JS
  - 笔记
  - TS
mp3:
cover: img/bg3.jpg
---

# Web Audio API

![](https://img-blog.csdnimg.cn/20200116182807152.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N3YWxsb3dibGFuaw==,size_16,color_FFFFFF,t_70)

### 实现功能

可视化、音色合成器、动态混音、声音特效、3D空间音频、均衡器、环境混响

## 一、基础使用

### 1.AudioContext

为音频处理提供一个上下文环境，相当于一个中央控制器，控制音频路由的各个模块；

### 1.1音频结点AudioNode

音频路由中的基本单位，工作依赖于AudioContext，音频结点拥有自己的输入输出，通过connect方法将一个节点的输出连接到另一个结点的输入。

```js
audioBufferSourceNode.connect(audioContext.destination)
```

- Souce Node:能产生音频的结点，只有输出没有输入
- Process Node:能对音频进行处理的结点，有多个输入和输出
- Destination Node:通常为音频播放设备

![img](https://pic3.zhimg.com/80/v2-35137da2f4932f059a1cfbb7ca291c8e_1440w.webp)

有的音频处理节点会有多个输出，比如ChannelSplitterNode，可以将音频拆分为多个声道，对应的，也有一个合并声道的节点ChannelMergerNode，有多个输入和一个输出。

### 1.2 路由图



