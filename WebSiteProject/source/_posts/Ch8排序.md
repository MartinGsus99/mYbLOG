---
title: 排序
date: 2021-08-31 20:57:45
categories: 
    - 编程
tags: 
    - C语言
mp3: 
cover: img/bg20.jpg
---


# 排序算法

## 一、插入排序

每次将一个待排序的记录插入到前面已经排序的序列；

```c
void InsertSort(RecordType R[],int num)
{
    int index1,index2;

    for(index1=2;index1<=num;index1++)
    {
       R[0]=R[index1];
       index2=index1-1;
       while(R[0].key<R[index2].key)
       {
           R[index2+1]=R[index2];
           index2--;
           R[index2+1]=R[0];
       }
    }
}
```

适用于一个基本有序的序列，n^2,稳定的；

## 二、希尔排序

又名缩小增量排序，按照下标增量分成若干个子序列，对每个子序列进行直接插入排序；一轮结束后缩小增量，划分子序列；

```c
void ShellSort(RecordType R[],int num)
{
    int index1,index2;
    int increasement;    //增量

    for(increasement=num/2;increasement>0;increasement=increasement/2)
    {
        for(index1=increasement+1;index1<=num;index1++)
        {
            R[0]=R[index1];
            index2=index1-increasement;
            while(index2>=0&&R[0].key<R[index2].key)
            {
                R[index2+increasement]=R[index2];
                index2=index2-increasement;
            }
            R[index2+increasement]=R[0];
        }
    }
    return;
}
```

空间复杂度O（1），适合大批量杂乱无章的数据序列，不稳定；

## 三、冒泡排序

每一轮按序比较相邻的两个数据，每一轮将最大的一个或最小的一个排序到最后；

```c
void BubbleSort(RecordType r[],int num)
{
    int index1,index2;
    int isExchange;
    for(index1=1;index1<num;index1++)
    {
        isExchange=0;
        for(index2=1;index2<=num-1;index2++)
        {
            if(r[index2].key>r[index2].key)
            {
                r[0]=r[index2+1];
                r[index2+1]=r[index2];
                r[index2]=r[0];
                isExchange=1;
            }
        }
        if(isExchange)
        {
            break;
        }
    }
}
```

时间复杂度O（n^2）,空间复杂度O（1），稳定的；

## 四、快速排序



```c
int Partition(RecordType R[],int low,int high)
{
    R[0]=R[low];
    while(low<high)
    {
        while(low<high&&R[high].key>=R[0].key)
        {
            --high;
        }
        R[low]=R[high];
        while(low<high&&R[low].key<=R[0].key)
        {
            ++low;
        }
        R[high]=R[low];
    }
    R[low]=R[0];
    return low;
}

void Quicksort(RecordType R[],int low,int high)
{
    int loc;
    if(low<high)
    {
        loc=Partition(R,low,high); 
        Quicksort(R,low,loc-1);
        Quicksort(R,loc+1,high);
    }
}
```

空间复杂度O(1),时间复杂度O（n^2）

## 五、折半插入排序

使用直接插入排序，使用折半查找需要插入的位置；

```c
void BinarySort(RecordType R[],int num)
{
    int index1,index2;
    int lowPoint,highPoint,midPoint;
    for(index1=1;index1<=num;index1++)
    {
        R[0]=R[index1];
        lowPoint=1;
        highPoint=index1-1;
        while(lowPoint<=highPoint)
        {
            midPoint=(lowPoint+highPoint)/2;
            if(R[0].key<R[midPoint].key)
            {
                highPoint=midPoint-1;
            }
            else
            {
                lowPoint=midPoint+1;
            }
        }
        for(index2=index1-1;index2>=highPoint+1;--index2)
        {
            R[index2+1]=R[index2];
        }
        R[highPoint+1]=R[0];
    }
}
```

