---
title: 顺序表
date: 2021-08-08 20:57:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/bg1.jpg
---

CH1 顺序表基本操作及实现（C）

```csharp
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 50
#define Elemtype int 

typedef struct{
    Elemtype data[MAXSIZE];
    int length;
}Sqlist;

void InitSqlist(Sqlist *L)
{
    L->length=0;
    printf("Init the list successfully!\n");
    return;
}

void CreateSqlist(Sqlist *L,int temp_data[],int temp_length)
{
    if(temp_length>MAXSIZE)
    {
        printf("Overflow!\n");
        return;
    }

    for(int index=0;index<temp_length;index++)
    {
        L->data[index]=temp_data[index];
    }
    L->length=temp_length;
    printf("Create the table successfully!\n");
    return;
}

void InsertList(Sqlist *L,Elemtype newData,int temp_position)
{
    if(temp_position<0||temp_position>L->length+1)
    {
        printf("Wrong position!\n");
        return;
    }
    else
    {
        for(int index=L->length;index>temp_position;index--)
        {
            L->data[index]=L->data[index-1];
        }
        L->data[temp_position]=newData;
        printf("Add new data successfully!\n");
        return;
    }
}

void DeleteDataByElement(Sqlist *L,Elemtype deletedData)
{
    int counter=0;
    for(int index=0;index<L->length-1;index++)
    {
        if(L->data[index]==deletedData)
        {
            counter+=1;
            for(int index1=index;index1<L->length-1;index1++)
            {
                L->data[index1]=L->data[index1+1];
            }
        }
    }
    L->length-=counter;
    printf("The counter is %d\n",counter);
    printf("Delete the data successfully!\n");
    return;
}

void DeleteDataByPosition(Sqlist *L,int tempDeletePosition)
{
    Elemtype deleted_data;
    if(tempDeletePosition<0||tempDeletePosition>L->length)
    {
        printf("Wrong position!\n");
    }
    else{
        deleted_data=L->data[tempDeletePosition];
        for(int index=tempDeletePosition;index<L->length;index++)
        {

            L->data[index]=L->data[index+1];
        }
        L->length--;
    }
    printf("Delete the data successfully!\n");
    printf("The deleted data is %d\n",deleted_data);
    return;
}

//按值查找
int Locate_Data(Linklist L,ElemType targetData)
{
    LNode *p;
    p=L->next;
    int index=0;
    while(p)
    {
        if(p->data==targetData)
        {
            printf("Position:%d.\n",index);
            return index;
        }
        index++;
        p=p->next;
    }
    printf("No such a data.\n");
    return -1;
}

//计算链表长度
int CountLinklistLength(Linklist L)
{
    int count=0;
    LNode *p;
    p=L->next;
    while(p)
    {
        count++;
        p=p->next;
    }
    printf("List length : %d.\n",count);
    return count;
}

void PrintList(Sqlist *L)
{
    printf("The list is below:\n");
    for(int index=0;index<L->length;index++)
    {
        printf("%d ",L->data[index]);
    }
    printf("\nThe length is %d\n",L->length);
    return;
}

//不确定是否正确
// void EmptyList(Sqlist *L)
// {
//     free(L->data);
//     L->length=0;
//     return;
// }



int main(){
    int my_data[MAXSIZE]={1,2,3,4,5,6,4,3,22,1};
    int my_length=10;
    Sqlist my_list;
    Elemtype insertData=10;
    int my_new_position=3;
    int my_abandoned_data=3;
    int my_deleted_position=2;

    InitSqlist(&my_list);
    CreateSqlist(&my_list,my_data,my_length);
    InsertList(&my_list,insertData,my_new_position);
    PrintList(&my_list);
    DeleteDataByElement(&my_list,my_abandoned_data);
    DeleteDataByPosition(&my_list,my_deleted_position);
    // EmptyList(&my_list);
    PrintList(&my_list);
    return 0;
}
```

统一使用头节点后的代码实现：

```csharp
Linklist Create_Linklist(int n)
{
    LNode *L,*p,*q;
    int i;
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;           //Head node;
    q=L;                    //q->L;
    for(i=0;i<n;i++)
    {
        p=(LNode*)malloc(sizeof(LNode));
        printf("Pelase enter data %d:",i);
        scanf("%d",&p->data);			 //q=L,p赋值
        p->next=NULL;					//q=L, p->NULL
        q->next=p;						//q->p->NULL==L->p->null;
        q=p;							
    }									
    return L;
}

int InsertData(Linklist L,ElemType data,int pos)
{
    LNode *p,*s;
    int index;
    p=L;
    index=-1;						//index设置为-1，则从0开始计算链表长度
    while(p&&index<pos-1)			//循环找到目标元素的前一个元素
    {
        p=p->next;
        index++;
    }
    if(!p||index>pos-1)				//p的下一个为空则不存在；index大于pos则出错；
    {
        printf("Wrong position.\n");
        return -1;
    }
    s=(LNode*)malloc(sizeof(LNode));	//创建新空间
    s->data=data;					
    s->next=p->next;			//s=target
    p->next=s;					//p->s,s->target
    printf("Insert the data successfully.\n");
    return 1;
}

int DeleteData(Linklist L,ElemType *e,int pos)   //*e可以获得目标元素的地址
{
    LNode *p,*q;
    p=L->next;							
    int index=-1;
    while(p->next&&index<pos-1)
    {
        p=p->next;
        index++;
    }
    if(!(p->next)||index>pos-1)
    {
        printf("Wrong position.\n");
        return -1;
    }
    q=p->next;
    *e=q->data;					//将data传入e
    p->next=q->next;
    free(q);
    printf("Get the data: %d\n",*e);
    return 1;

}

//合并两个有序链表，且合成的链表也是顺序的
Linklist MergeLinklist(Linklist A,Linklist B)
{
    LNode *pa,*pb,*pc,*C;
    pa=A->next;
    pb=B->next;
    C=pc=A;						//C=A
    while(pa&&pb)
    {
        if(pa->data<=pb->data)
        {
            pc->next=pa;		//c->a1;
            pc=pa;				//c=a1;
            pa=pa->next;		//a1=a2
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    pc->next=pa?pa:pb;
    free(B);
    return C;

}

void PrintLinklist(Linklist L)
{
    LNode *p;
    p=L->next;
    printf("DATA OUTPUT:");
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    int e;

    Linklist MyLinklist;
    MyLinklist=Create_Linklist(5);
    PrintLinklist(MyLinklist);
    InsertData(MyLinklist,101,3);
    PrintLinklist(MyLinklist);
    DeleteData(MyLinklist,&e,3);    //Use & to get data;
    PrintLinklist(MyLinklist);



    return 0;
}
```

二、双向链表

```c
#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

//节点结构
typedef struct DulNode{
    struct DulNode * prior;
    int data;
    struct DulNode * next;
}DulNode,*DulLinkList;

DulNode* initDulNode(DulNode * L,int length){
    //创建一个首元节点，链表的头指针为L
    L=(DulNode*)malloc(sizeof(DulNode));
    //对节点进行初始化
    L->prior=NULL;
    L->next=NULL;
    L->data=NULL;
    //声明一个指向首元节点的指针，方便后期向链表中添加新创建的节点
    DulNode *r=L;
    for (int count=0; count<length; count++) {
        //创建新的节点并初始化
        DulNode *p=(DulNode*)malloc(sizeof(DulNode));
        p->prior=NULL;
        p->next=NULL;
        printf("Please enter data %d:",count);
        scanf("%d",&p->data);
        //新节点与链表最后一个节点建立关系
        r->next=p;
        p->prior=r;
        //r永远指向链表中最后一个节点，重点！！！！
        r=r->next;
    }
    //返回新创建的链表
    return L;
}
void display(DulNode * L){
    DulNode *temp=L->next;
    while (temp) {
        //如果该节点无后继节点，说明此节点是链表的最后一个节点
        if (temp->next==NULL) {
            printf("%d\n",temp->data);
        }else{
            printf("%d <-> ",temp->data);
        }
        temp=temp->next;
    }
}


int main() {
    //创建一个头指针
    DulNode * L=NULL;
    //调用链表创建函数
    L=initDulNode(L,5);
    //输出创建好的链表
    display(L);
    //显示双链表的优点
    return 0;
}


```

