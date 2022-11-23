---
title: 关于C语言的一些奇奇怪怪
date: 2021-08-08 20:56:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/2.jpg
---

```csharp
#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 5
#define INCREMENT 2

typedef int ElemType;
typedef struct{
    ElemType *data;
    int length;
    int list_length;
}SqList;

int InitList_Sq(SqList *L)
{
    L->data=(ElemType *)malloc(INIT_SIZE*sizeof(ElemType));
    if(!L->data){
        return -1;
    }
    L->length=0;
    L->list_length=INIT_SIZE;
    return 1;
}

int ListInsert(SqList *L,int index,ElemType temp_data)
{
    int j;
    ElemType *newBase;
    if(index<0 || index>L->length)
    {
        //realloc重新分配
        newBase=(ElemType *)realloc(L->data,(L->list_length+INCREMENT)*sizeof(ElemType));
        if(!newBase)
        {
            return -1;
        }
        L->data=newBase;
        L->list_length+=INCREMENT;
    }
    for(j=L->length-1;j>=index;j--)
    {
        L->data[j+1]=L->data[j];
    }
    L->data[index]=temp_data;
    L->length++;
    return 1;
}

int DeleteList(SqList *L,int pos)
{
    if(pos<0||pos>L->length)
    {
        printf("Wrong position.\n");
        return 0;
    }
    for(int index=pos;index<L->length;index++)
    {
        L->data[index]=L->data[index+1];
    }
    L->length--;
    return 1;
}

int FindElem(SqList *L,ElemType target)
{
    if(!L->data)
    {
        printf("Empty table.\n");
        return -1;
    }
    for(int index=0;index<L->length;index++)
    {
        if(target==L->data[index])
        {
            printf("Find at %d.\n",index);
            return index;
        }
    }
    printf("No such a data.\n");
    return -1;
}

void PrintList(SqList *L)
{
    for(int index=0;index<L->length;index++)
    {
        printf("%d ",L->data[index]);
    }
    printf("\n");
}


int main()
{
    SqList *Mylist;
    InitList_Sq(Mylist);

    for(int count=0;count<INIT_SIZE;count++)
    {
        ListInsert(Mylist,0,count);
    }

    PrintList(Mylist);

    DeleteList(Mylist,3);

    PrintList(Mylist);
    printf("Find 2 in %d.\n",FindElem(Mylist,2));
    return 0;
}

```

实现了顺序表的初始化、创建、增加（n）、删除(n)、查找(n)；