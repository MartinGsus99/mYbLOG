# Shell基础

## 一、标准输入和参数的区别

```sh
#$ 开启参数输入
rm $(where con.sh) 
```

> 标准输入就是编程语言中诸如`scanf`或者`readline`命令，而参数指程序的main函数传入的`args`字符数组

- 管道符和重定向符是将数据作为程序的标准输入，而`$(cmd)`是将命令输出的数据作为参数

```shell
#rm不接受标准输入

#cat即接受标准输入也接受命令行参数
```

## 二、后台运行程序

```shell
#启动Django
python manager.py runserver 0.0.0.0
```

此时，终端被阻塞，除非终止进程

```shell
# 末尾加 $ 来让终端继续响应
（python manager.py runserver 0.0.0.0 &）
```

> 每一个终端都是一个shell进程，如果关掉shell端口则所有依附的子进程都会退出
>
> 而 （cmd &）则是让 `systemd`系统守护进程

## 三、使用技巧

- 输入相似文件名太麻烦

```shell
echo {one,two,three}file
echo {one,two,three}{1,2,3}
```

- 输入路径名称太麻烦

```shell
#当前目录
pwd
#返回home
cd
#在会上一个目录
cd -
#替换上一个目录
chmod +x !$

#替换上一个目录所有文件路径
chmod +x !*
```

- 重复命令

```shell
#自动替换上一个命令
!!
```

