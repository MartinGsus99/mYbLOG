---
title: CH7 查找
date: 2021-08-25 20:57:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/bg3.jpg
---

## 一、顺序查找

MSL最大查找长度，ASL平均查找长度；

ASL成功=SumPi（n-i+1） ASL失败=n+1

```c
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int keyType;
typedef struct
{
    keyType key;
} SElemType;

typedef struct
{
    SElemType *elem;
    int length;
} SeqTable;

int Search_Seq(SeqTable ST)
{
    int index;
    keyType key;
    printf("Enter the target:");
    scanf("%d",&key);
    ST.elem[ST.length].key=key;
    for(index=0; ST.elem[index].key!=key; ++index);
    if(index<ST.length)
    {
        printf("Find in %d",index);
        return index;
    }
    else return -1;
}

void main()
{
    SeqTable SQT;
    keyType key;
    int index;
    SElemType Data[MAXSIZE]= {34,44,43,12,53,55,73,64,77};
    SQT.elem=Data;
    SQT.length=9;
    index=Search_Seq(SQT);
}
//若找不到报错，检查scanf函数是否添加了&符号v(#｀-_ゝ-)

```



## 二、折半查找(静态)

必须使用顺序存贮且元素按照关键字升序；

```c
#include<stdio.h>

#define MAXSIZE 100

typedef int keyType;

typedef struct
{
    keyType key;
}SElemType;

typedef struct
{
    SElemType *elem;
    int length;
}SeqTable;

int SearchBin(SeqTable ST)
{
    int low,mid,high;
    low=0;
    high=ST.length-1;
    keyType target;
    printf("Enter the target:");
    scanf("%d",&target);
    while(low<=high)
    {
        mid=(low+high)/2;
        printf("low:%d,mid:%d,high:%d\n",low,mid,high);
        if(target==ST.elem[mid].key)
        {
            printf("Find in position %d.",mid);
            return mid;
        }
        else if(target<ST.elem[mid].key)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return -1;
}

void main()
{
        SeqTable T;
        int index;
        SElemType DATA[MAXSIZE]={10,13,15,20,65,66,90,100,120};
        T.elem=DATA;
        T.length=9;
        index=SearchBin(T);
        if(index==-1)
        {
            printf("No such a data.\n");
        }
}

#include<stdio.h>

#define MAXSIZE 100

typedef int keyType;

typedef struct
{
    keyType key;
}SElemType;

typedef struct
{
    SElemType *elem;
    int length;
}SeqTable;

int SearchBin(SeqTable ST)
{
    int low,mid,high;
    low=0;
    high=ST.length-1;
    keyType target;
    printf("Enter the target:");
    scanf("%d",&target);
    while(low<=high)
    {
        mid=(low+high)/2;
        printf("low:%d,mid:%d,high:%d\n",low,mid,high);
        if(target==ST.elem[mid].key)
        {
            printf("Find in position %d.",mid);
            return mid;
        }
        else if(target<ST.elem[mid].key)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return -1;
}

void main()
{
        SeqTable T;
        int index;
        SElemType DATA[MAXSIZE]={10,13,15,20,65,66,90,100,120};
        T.elem=DATA;
        T.length=9;
        index=SearchBin(T);
        if(index==-1)
        {
            printf("No such a data.\n");
        }
}


```



## 三、二叉排序树查找（动态）

二叉树中所有的左孩子小于其父节点，右孩子大于其父节点

若根节点的左右子树高度差不超过1，则称为平衡二叉树；ASL=log2（n）

```c
#include<stdio.h>
#include<stdlib.h>

typedef int keyType;

typedef struct BTNode
{
    keyType key;
    struct BTNode *lchild,*rchild;
}BTNode,*BiTree;

BiTree SearchBSTree(BTNode *T,keyType key)
{
    if(!T||key==T->key) return T;
    else if(key<T->key) return(SearchBSTree(T->lchild,key));
    else return(SearchBSTree(T->rchild,key));
}

BTNode *SearchBST(BTNode *T,keyType key,int *flag)
{
    BTNode *p,*pre;
    //flag==1，查找成功，返回该元素节点；否则查找失败，返回访问的最后一个节点；
    *flag=0;
    if(!T)
    {
        *flag=0;
        return T;
    }
    p=T;
    pre=T;
    while(p!=NULL&&key!=p->key)
    {
        pre=p;
        if(key<p->key) p=p->lchild;
        else p=p->rchild;
    }
    if(p!=NULL&&key==p->key)
    {
        *flag=1;
        return p;
    }
    else
    {
        *flag=0;
        return pre;
    }
}

BTNode *InsertBSTNode(BTNode *T,keyType key)
{
    BTNode *p,*s;
    int flag=0;
    //查找是否存在相同节点
    p=SearchBST(T,key,&flag);
    if(!flag)
    {
        s=(BTNode*)malloc(sizeof(BTNode));
        s->key=key;
        s->lchild=s->rchild=NULL;
        if(!p)
        {
            return s;
        }
        else if(key<p->key) p->lchild=s;
        else p->rchild=s;
    }
    return T;
}

BiTree Create(keyType key)
{

    BiTree T;
    T=(BTNode*)malloc(sizeof(BTNode));
    if(T==NULL)
    {
        printf("Asaign the memory failurely.");
        return NULL;
    }
    T->key=key;
    T->lchild=T->rchild=NULL;
    return T;
}

void VisitNode(keyType key)
{
    printf("%d ",key);
}

void InorderTree(BiTree T)
{
    if(T!=NULL)
    {
        InorderTree(T->lchild);
        VisitNode(T->key);
        InorderTree(T->rchild);
    }
}


void main()
{

    BTNode *ST;
    keyType mykey;
    int index,nums;
    printf("Enter the nodes' number:");
    scanf("%d",&nums);
    printf("Please enter the root's data:");
    scanf("%d",&mykey);
    ST=Create(mykey);

    for(index=1;index<nums;index++)
    {
        keyType tmp_key;
        printf("Please enter the %d node:",index);
        scanf("%d",&tmp_key);
        ST=InsertBSTNode(ST,tmp_key);
    }
    InorderTree(ST);
    printf("Please enter the target data:");
    scanf("%d",&mykey);
    ST=SearchBSTree(ST,mykey);
    if(!ST)
    {
        printf("No such a data.\n");
    }
    else
    {
        printf("Find it:%d!",mykey);
    }

}

```



## 四、哈希表

### 1.适用于动态查找和静态查找

### 2.常见哈希函数

（1）直接定址：适合连续的分布；

（2）除留取余：假定哈希表长m,取p<=m，一般选择不大于m的最大质数；

### 3.处理冲突的方法

（1）开放地址：Hi=(H(Key)+di)%m;

​		i.线性探测法：若计算出的地址冲突，则一次向后顺延；容易造成聚集（堆积），降低查找效率；

​		ii.平方探测法：若计算出的地址冲突，则一次向后/前顺延i^2个地址；

（2）链地址：在冲突的数据位置设置链表；