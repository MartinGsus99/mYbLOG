---
title: Docker 一键部署
date: 2023-07-2 21:13:45
categories:
  - 运维
tags:
  - Docker

cover: img/bg1.jpg
---

# Docker 一键部署

## 一、基本操作

1. sudo passwd 安装完成 ubuntu 系统后，设置 root 密码
2. 切换至 root 管理员 su 3、git clone cd / && git clone http://用户名:密码@47.103.136.241/other/builder.git
3. 给脚本赋予可执行权限 chmod +x build.sh
4. 执行脚本 ./build.sh
5. 运行脚本，使用脚本进行初始环境安装 安装途中有步骤需要按[enter]操作四次左右
6. 运行脚本，使用脚本进行前端编译环境安装 安装途中有步骤需要按[enter]操作，如果出现报错忽略，再次执行
7. cd 到 builder 项目目录下，./builder.sh
8. 首先构建本地运行环境，选择公共功能，选择需要的后端环境
9. cd 到项目目录下，修改 setting.py 文件 ip
10. cd 到 server 目录，flask run
