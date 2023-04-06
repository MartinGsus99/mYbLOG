---
title: Linux Shell
date: 2023-04-06 18:51:45
categories: 
    - Linux
tags: 
    - shell
    - Linux
mp3: 
cover: img/bg11.jpg
---


# Linux Shell

- 标准输入和命令参数的区别；
- 后台运行命令在推出中断后也全部退出；
- 单引号和双引号表示字符串的区别；
- 有的命令和sudo一起用就会Command not found;

## 一、标准输入和参数的区别

### 1.标准输入和参数

```shell
#错误
where connect.sh | rm

#正确
rm $(where connect.sh)

```

> 标准输入就是编程语言中诸如scanf或者readline命令，而参数是指程序的main函数传入的args字符数组；
>
> 如果命令能够让终端阻塞，说明该命令接受标准输入，反之不接受；

### 2.后台运行程序

```shell
python manager.py run server 0.0.0.0
```

远程登录服务器然后启动Django服务，此时可以通过服务器IP测试，但是终端此时是阻塞状态；

可以在命令后加上`&`符号，命令行就不会阻塞，响应后续命令；

```sh
(python manager.py runserver 0.0.0.0  &)
```

> 每一个终端其实都是一个shell进程，在该终端执行的程序其实都是这个shell进程分出来的子进程；
>
> 正常情况下，shell进程会阻塞，等待子进程退出才重新接受新的命令；
>
> 加上`&`符号只是让shell进程不在阻塞可以继续响应命令，但是无论如何，一旦终端关闭，所有依附的子进程都会关闭；
>
> 而（cmd &）这样运行命令，则是将cmd命令挂到systemed系统守护进程；

```shell
nohub some_cmd &
```

### 3.单双引号的区别

> 不同的shell会有细微区别；
>
> 对于`$`,`()`,这几个符号，单引号包围的字符串不会做任何转义，双引号会；

- 如果`$`读出的参数字符包含空格，应该用双引号括起来，否则会出错；

### 4. sudo找不到命令

有时普通用户可以用的命令，加上sudo权限却无法使用；

- 原因在于该脚本仅存在于该用户的环境变量中；
- 解决方法是使用脚本文件的路径；

## 二、Linux Shell提高效率的技巧

### 1.相似文件名

```shell
# onefile twofile threefile
echo {one,two,three}file

#one1 one2 one3 two1 two2 two3 three1 three2 three3
echo {one,two,three}{1,2,3}
```

应用：命令拓展参数

```shell
#给file复制一个file.bak的副本
cp /path/file{,.bak} 

#删除file{1，3，5}
rm file{1,3,4}.txt

#移动相同类型文件
mv *.{c,cpp} src/
```

### 2. 输入路径名称太麻烦

```shell
#返回home
cd  

#返回上一个目录
cd -

# !$会替换上一次命令最后的路径
chmod +x !$

# !*会替换上一次命令输入的所有文件路径
chmod +x !*

# !! 自动使用上一个命令；
！！
```























