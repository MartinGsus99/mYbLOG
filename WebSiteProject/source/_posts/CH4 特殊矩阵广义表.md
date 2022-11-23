---
title: 特殊矩阵及广义表
date: 2021-08-20 20:57:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/bg16.jpg
---

一、对称矩阵

```csharp
void PrintSymetryMatrix(int m[],int n)
{
    int row,col;
    printf("Symetry Matrix:\n");
    for(row=0;row<n;row++)
    {
        for(col=0;col<n;col++)
        {
            if(row>=col)
            {
                printf("%4d ",m[row*(row+1)/2+col]);
            }
            else
            {
                printf("%4d ",m[col*(col+1)/2+row]);
            }
        }
        printf("\n");
    }
    return;
}
```

​					

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Elemtype;
#define MaxSize 100

typedef struct
{
    int rowIndex,colIndex;
    Elemtype data;
} TriUnitGroup;

typedef struct
{
    TriUnitGroup data[MaxSize+1];
    int unzeroNumber,colNumber,rowNumber;
} TSMatrix;

int main()
{
    TSMatrix *myMatrix;
    int myData[16]= {1,2,0,3,4,6,0,0,0,4,0,1,3,1,1,0};
    CreateM(&myMatrix,myData,4,4);
    PrintTripleUnitMatrix(&myMatrix);

    return 0;
}


int CreateM(TSMatrix *M,int data[],int row,int col)
{

    int index=0;
    int count=0;

    for(index=0; index<row*col; index++)
    {
        if(data[index]!=0)
        {
            M->data[count].rowIndex=index/col;
            M->data[count].colIndex=index%col;
            M->data[count].data=data[index];
            ++count;
            printf("%d Add data %d successfully.\n",count,data[index]);
        }
    }

    if(count>0)
    {
        printf("Data number:%d.\n",count);
        /*Errors here.*/
        M->unzeroNumber=count;
        M->colNumber=col;
        M->rowNumber=row;
        printf("Finished.\n");
        return 1;
    }
    else
    {
        printf("All data are 0.\n");
        printf("Finished.\n");
        return 0;
    }

}

void PrintTripleUnitMatrix(TSMatrix *M)
{
    printf("*  i  j  value\n");
    for(int index1=0; index1<M->unzeroNumber; index1++)
    {
        printf("%d  %d  %d  %d\n",index1,M->data[index1].rowIndex,M->data[index1].colIndex,M->data[index1].data);
    }
    return;
}


void PrintSymmetricArray(int array[],int col,int row)
{
    int col_index,row_index;

    for(col_index=0; col_index<col; col_index++)
    {
        for(row_index=0; row_index<row; row_index++)
        {
            if(col_index<=row_index)
            {
                printf("%d ",array[row_index*(row_index+1)/2+col_index]);
            }
            else
            {
                printf("%d ",array[col_index*(col_index+1)/2+row_index]);
            }
        }
        printf("\n");
    }
    return;
}

void PrintUpTriangle(int array[],int col,int row)
{
    for(int index1=0; index1<col; index1++)
    {
        for(int index2=0; index2<row; index2++)
        {
            if(index1<index2)
            {
                printf("%d ",array[0]);
            }
            else
            {
                printf("%d ",array[index1*(index1+1)/2+1+index2]);
            }
        }
        printf("\n");
    }
    return;
}

void PrintDownTriangle(int array[],int col,int row)
{
    for(int index1=0; index1<col; index1++)
    {
        for(int index2=0; index2<row; index2++)
        {
            if(index1>index2)
            {
                printf("%d ",array[0]);
            }
            else
            {
                printf("%d ",array[index2*(index2+1)/2+1+index1]);
            }
        }
        printf("\n");
    }
    return;
}


```

