---
title: AES算法
date: 2020-11-4 21:03:45
categories: 
    - 密码学
tags: 
    - 密码学
    - AES
mp3: 
cover: img/mimaxue.jpg
---

# `AES数学基础`

## 1.有限域GF(2^8)

AES以字节为单位进行计算，一个字节8bit。

多项式表示法：01010111———>x^6+x^4+x^2+x^1+x^0

## 2.算法的基本运算

### （1）加法、减法

​	**异或运算：01010111+10000011=11010100**

### （2）乘法

​	要计算有限域GF（2^8）上的乘法，需要确定一个GF(2)上的8次不可约多项式(除了1和自身没有任何其他因子)。

​	对于AES，这个不可约多项式确定为：m(x)=x^8+x^4+x^3+x^1+x^0 (二进制表示：0000000100011011)

​	在AES乘法中，需要将两数积mod m(x)。

​	**例：01010111*10000011=11000001**

### （3）X乘运算

 	xtime()算法可用于面向字节的乘法运算。

​	根据定义，xtime()运算是最高项指数不大于7的多项式b(x)乘以多项式x的乘法运算

​	例：b(x)=b7x7+b6x6+b5x5+b4x4+b3x3+b2x2+b1x+b0
​	xtime(b(x))=x·b(x)=(b7x8+b6x7+b5x6+b4x5+b3x4+b2x3+b1x2+b0x )mod m(x)
​	=(b7x8+b6x7+b5x6+b4x5+b3x4+b2x3+b1x2+b0x )mod (x8+x4+x3+x+1)

分类讨论：

（1）当b7=0：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201104210055963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)


（2）当b7=1：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201104210107640.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)




# 	AES算法描述

## 	1.概述

​	分组长度：128bit		密钥长度：128bit、192bit、256bit（密钥长度不同，加密轮数不同）

​	基于Rijndael算法。

## 	2.算法原理

​	**例：**

​    已知：一轮输入状态矩阵：

​	**EA 04 65 85**

​	 **83 45 5D 96**  

 	**5C 33 98 B0**

​	 **F0 2D AD C5**

### （1）字节代换：关于字节的非线性变换（利用S盒）。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201104210124399.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)

代换结果：

**87 F2 4D 97
EC 6E 4C 90
4A C3  46  E7
8C D8 95  A6**

### （2）行位移：将状态矩阵各行进行循环位移

​	第一行保持不变，第二行循环左移8bit，第三行循环左移16bit，第四行循环左移24bit

位移结果：

**87    f2    4d    97
6e    4c    90    ec   	（左1）
46    e7    4a    c3		（左2）
a6    8c    d8    95**		（左3）

### （3）列混淆：将状态矩阵**右乘**列混淆矩阵，这个过程称为列混淆

混淆矩阵：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201104210138340.png#pic_center)



![在这里插入图片描述](https://img-blog.csdnimg.cn/20201104210149908.png#pic_center)


混淆结果：

**47    40    a3    4c
37    d4    70    9f
94    e4    3a    42
ed    a5    a6    bc**

### （4）轮密钥加：用轮密钥矩阵的第 i 列，与上面得到的列混淆矩阵的第 i 列进行异或运算，得到最后的矩阵。



### 3.代码实现（C语言）

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;
 
int a[4][4] = {
    {0x87, 0xF2, 0x4D, 0x97},
    {0xEC, 0x6E, 0x4C, 0x90},
    {0x4A, 0xC3, 0x46, 0xE7},
    {0x8C, 0xD8, 0x95, 0xA6}
};//字节代换后的矩阵
int mixCol[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};//列混淆矩阵
int round_key[4][4] = {
    {0xAC, 0x19, 0x28, 0x57},
    {0x77, 0xFA, 0xD1, 0x5C},
    {0x66, 0xDC, 0x29, 0x00},
    {0xF3, 0x21, 0x41, 0x6A},
};//轮密钥矩阵
 
int b[4][4];//行移位后的矩阵
int resMix[4][4];//列混淆后的矩阵
int res[4][4];//轮密钥加后的矩阵
 
int mul_mat(int x,int y) {
    if(x == 0x01) {
        return y;
    }
    else if(x == 0x02) {
        if((y&128) != 128) { //二进制首位为0
            return y<<1;
        }
        else {
            int temp = ((y<<1)&((1<<8)-1)); //向左移一位，删掉最高位(保留8位)
            return temp^(0x1b);
        }
    }
    else if(x == 0x03) {
        return mul_mat(0x02,y)^y;
    }
}
 
 
int main() {
 
    cout<<"字节代换后的矩阵为："<<endl;
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            cout<<hex<<a[i][j]<<'\t';
        }
        cout<<endl;
    }
 
    //行移位
    for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
            b[i][j] = a[i][(i+j)%4];
 
    cout<<"行移位后的矩阵为："<<endl;
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            cout<<hex<<b[i][j]<<'\t';
        }
        cout<<endl;
    }
 
    //列混淆
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            for(int k=0;k<=3;k++) {
                resMix[i][j] ^= mul_mat(mixCol[i][k],b[k][j]);
            }
        }
    }
    cout<<"列混淆后的矩阵为："<<endl;
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            cout<<hex<<resMix[i][j]<<'\t';
        }
        cout<<endl;
    }
 
    //轮密钥加
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            res[j][i] = resMix[j][i] ^ round_key[j][i];
        }
    }
    cout<<"轮密钥加后的矩阵为："<<endl;
    for(int i=0;i<=3;i++) {
        for(int j=0;j<=3;j++) {
            cout<<hex<<res[i][j]<<'\t';
        }
        cout<<endl;
    }
}
```


