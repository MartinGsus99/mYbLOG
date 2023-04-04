---
title: 树
date: 2021-08-21 20:57:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/bg22.jpg
---
# Ch 5 树

## 一、二叉树及其性质

（1）二叉树可以为空，但是二叉有序树至少三个节点；

（2）满二叉树：2^k-1个节点、

（3）非空二叉树第i层的节点数不超过2^i-1个；

（4）深度为k的二叉树最少k个节点，最多2^k-1个节点；

（5）n0=n2-1;

（6）n个节点的二叉树深度为Log2 N-1；

（7）完全二叉树中，节点i的双亲节点为[i/2],左孩子2i，有孩子2i+1；

## 二、二叉树的实现及常用操作

### 1.二叉树的基本操作

```c
#include<stdio.h>
#include<stdlib.h>
#define MAXNODE 10

typedef int Elemtype ;

typedef struct BiTreeNode
{
    Elemtype data;
    struct BiTreeNode *lchild,*rchild;
} BiTreeNode,*BiTree;

typedef struct BiTreeParNode
{
    Elemtype data;
    struct BiTreeParNode *lchild,*rchild,*parent;
} BiParTreeNode,*BiParTree;

void Initiate(BiTree T)
{
    if((T=(BiTreeNode*)malloc(sizeof(BiTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return;
    }
    T->lchild=NULL;
    T->rchild=NULL;
    return;
}

BiTree CreateTree(Elemtype x)
{
    BiTree p;
    if((p=(BiTree *)malloc(sizeof(BiTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    return p;
}

BiTree InsertTreeLeftNode(BiTree T,Elemtype x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("No such a parent.\n");
        return NULL;
    }
    if((p=(BiTree*)malloc(sizeof(BiTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->lchild==NULL)
    {
        parent->lchild=p;
    }
    else
    {
        p->lchild=parent->lchild;
        parent->lchild=p;
    }
    printf("Insert data %d to leftchild.\n",x);
    return T;
}

BiTree InsertTreeRightNode(BiTree T,Elemtype x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("No such a parent.\n");
        return NULL;
    }
    if((p=(BiTree*)malloc(sizeof(BiTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->rchild==NULL)
    {
        parent->rchild=p;
    }
    else
    {
        p->rchild=parent->rchild;
        parent->rchild=p;
    }
    printf("Insert data %d to rightchild.\n",x);
    return T;
}

BiTree DeleteTreeLeftNode(BiTree T,BiTree parent)
{
    BiTree p;
    if(parent==NULL||parent->lchild==NULL)
    {
        printf("No left child.\n");
        return NULL;
    }
    p=parent->lchild;
    parent->lchild=NULL;
    free(p);
    return T;
}

BiTree DeleteTreeRightNode(BiTree T,BiTree parent)
{
    BiTree p;
    if(parent==NULL||parent->rchild==NULL)
    {
        printf("No left child.\n");
        return NULL;
    }
    p=parent->rchild;
    parent->rchild=NULL;
    free(p);
    return T;
}

int PreOrderTree(BiTree T)
{
    if(T==NULL)
    {
        return;
    }
    Visit(T->data);
    PreOrderTree(T->lchild);
    PreOrderTree(T->rchild);

}

int MiddleOrderTree(BiTree T)
{
    if(T==NULL)
    {
        return;
    }
    MiddleOrderTree(T->lchild);
    Visit(T->data);
    MiddleOrderTree(T->rchild);

}

int LastOrderTree(BiTree T)
{
    if(T==NULL)
    {
        return;
    }
    LastOrderTree(T->lchild);
    LastOrderTree(T->rchild);
    Visit(T->data);

}

void LevelOrderTree(BiTree T)
{
    BiTree Queue[MAXNODE];
    int front,rear;

    if(T==NULL)
    {
        return;
    }
    front=-1;
    rear=-1;
    Queue[++rear]=T;
    while(front!=rear)
    {
        Visit(Queue[++front]->data);
        if(Queue[front]->lchild!=NULL)
        {
            Queue[++rear]=Queue[front]->lchild;
        }
        if(Queue[front]->rchild!=NULL)
        {
            Queue[++rear]=Queue[front]->rchild;
        }
    }
}

void Visit(Elemtype data)
{
    printf("%3d",data);
}


int main()
{
    BiTree myTree;
    Elemtype rootData;
    int numberOfNodes,index,choice;

    printf("Please enter the node number:\n");
    scanf("%d",&numberOfNodes);
    printf("Please enter the data of root node:");
    scanf("%d",&rootData);

    myTree=CreateTree(rootData);

    for(index=1; index<numberOfNodes; index++)
    {
        printf("No %d node's position is:\n1.Leftchild of Root.\n2.Rightchild of Root.\n3.Leftchild of the Root's leftchild.\n4.Rightchild of the Root's leftchild.\n5.Leftchild of the Root's rightchild.\n6.Rightchild of the Root's rightchild.\n",index);
        printf("Choice:");
        scanf("%d",&choice);
        printf("Please enter the %d data:",index);
        Elemtype nodedata;
        scanf("%d",&nodedata);
        switch(choice)
        {
        case 1:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree);
            break;
        case 2:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree);
            break;
        case 3:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree->lchild);
            break;
        case 4:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree->lchild);
            break;
        case 5:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree->rchild);
            break;
        case 6:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree->rchild);
            break;
        }
    }
    printf("Preorder:");
    PreOrderTree(myTree);
    printf("\n");
    printf("Middleorder:");
    MiddleOrderTree(myTree);
    printf("\n");
    printf("Postorder:");
    LastOrderTree(myTree);
    printf("\n");
    printf("Leverorder:");
    LevelOrderTree(myTree);
    printf("\n");

    return 0;
}




```

### 2.线索二叉树的基本操作

```c
#include<stdio.h>
#include<stdlib.h>
#define MAXNODE 10

typedef int Elemtype ;

typedef struct BiThrTreeNode
{
    Elemtype data;
    struct BiThrTreeNode *lchild;
    struct BiThrTreeNode *rchild;
    unsigned ltag:1;
    unsigned rtag:1;
} BiThrTreeNode,*BiThrTree;

BiThrTree pre;


void Visit(Elemtype data)
{
    printf("%3d",data);
}


BiThrTree CreateTree(Elemtype x)
{
    BiThrTree p;
    if((p=(BiThrTree *)malloc(sizeof(BiThrTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    return p;
}

BiThrTree InsertTreeLeftNode(BiThrTree T,Elemtype x,BiThrTree parent)
{
    BiThrTree p;
    if(parent==NULL)
    {
        printf("No such a parent.\n");
        return NULL;
    }
    if((p=(BiThrTree*)malloc(sizeof(BiThrTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->lchild==NULL)
    {
        parent->lchild=p;
        parent->ltag=0;
    }
    else
    {
        p->lchild=parent->lchild;
        parent->lchild=p;
        parent->ltag=0;
    }
    printf("Insert data %d to leftchild.\n",x);
    return T;
}

BiThrTree InsertTreeRightNode(BiThrTree T,Elemtype x,BiThrTree parent)
{
    BiThrTree p;
    if(parent==NULL)
    {
        printf("No such a parent.\n");
        return NULL;
    }
    if((p=(BiThrTree*)malloc(sizeof(BiThrTreeNode)))==NULL)
    {
        printf("Empty tree.\n");
        return NULL;
    }
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->rchild==NULL)
    {
        parent->rchild=p;
        parent->rtag=0;
    }
    else
    {
        p->rchild=parent->rchild;
        parent->rchild=p;
        parent->rtag=0;
    }
    printf("Insert data %d to rightchild.\n",x);
    return T;
}


int MiddleOrderTree(BiThrTree T)
{
    if(T==NULL)
    {
        return;
    }
    MiddleOrderTree(T->lchild);
    Visit(T->data);
    MiddleOrderTree(T->rchild);

}

BiThrTree MiddleOrderThr(BiThrTree T)

BiThrTree DeleteTreeLeftNode(BiThrTree T,BiThrTree parent)
{
    BiThrTree p;
    if(parent==NULL||parent->lchild==NULL)
    {
        printf("No left child.\n");
        return NULL;
    }
    p=parent->lchild;
    parent->lchild=NULL;
    free(p);
    return T;
}

BiThrTree DeleteTreeRightNode(BiThrTree T,BiThrTree parent)
{
    BiThrTree p;
    if(parent==NULL||parent->rchild==NULL)
    {
        printf("No left child.\n");
        return NULL;
    }
    p=parent->rchild;
    parent->rchild=NULL;
    free(p);
    return T;
}

int PreOrderTree(BiThrTree T)
{
    if(T==NULL)
    {
        return;
    }
    Visit(T->data);
    PreOrderTree(T->lchild);
    PreOrderTree(T->rchild);

}



int LastOrderTree(BiThrTree T)
{
    if(T==NULL)
    {
        return;
    }
    LastOrderTree(T->lchild);
    LastOrderTree(T->rchild);
    Visit(T->data);

}

void LevelOrderTree(BiThrTree T)
{
    BiThrTree Queue[MAXNODE];
    int front,rear;

    if(T==NULL)
    {
        return;
    }
    front=-1;
    rear=-1;
    Queue[++rear]=T;
    while(front!=rear)
    {
        Visit(Queue[++front]->data);
        if(Queue[front]->lchild!=NULL)
        {
            Queue[++rear]=Queue[front]->lchild;
        }
        if(Queue[front]->rchild!=NULL)
        {
            Queue[++rear]=Queue[front]->rchild;
        }
    }
}



int main()
{
    BiThrTree myTree;
    Elemtype rootData;
    int numberOfNodes,index,choice;

    printf("Please enter the node number:\n");
    scanf("%d",&numberOfNodes);
    printf("Please enter the data of root node:");
    scanf("%d",&rootData);

    myTree=CreateTree(rootData);

    for(index=1; index<numberOfNodes; index++)
    {
        printf("No %d node's position is:\n1.Leftchild of Root.\n2.Rightchild of Root.\n3.Leftchild of the Root's leftchild.\n4.Rightchild of the Root's leftchild.\n5.Leftchild of the Root's rightchild.\n6.Rightchild of the Root's rightchild.\n",index);
        printf("Choice:");
        scanf("%d",&choice);
        printf("Please enter the %d data:",index);
        Elemtype nodedata;
        scanf("%d",&nodedata);
        switch(choice)
        {
        case 1:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree);
            break;
        case 2:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree);
            break;
        case 3:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree->lchild);
            break;
        case 4:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree->lchild);
            break;
        case 5:
            myTree=InsertTreeLeftNode(myTree,nodedata,myTree->rchild);
            break;
        case 6:
            myTree=InsertTreeRightNode(myTree,nodedata,myTree->rchild);
            break;
        }
    }
    printf("Preorder:");
    PreOrderTree(myTree);
    printf("\n");
    printf("Middleorder:");
    MiddleOrderTree(myTree);
    printf("\n");
    printf("Postorder:");
    LastOrderTree(myTree);
    printf("\n");
    printf("Leverorder:");
    LevelOrderTree(myTree);
    printf("\n");

    return 0;
}




```

### 3.哈夫曼树

