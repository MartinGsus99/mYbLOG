---
title: 数据结构
date: 2021-04-09 18:03:45
categories: 
    - 算法
tags: 
    - 笔记
    - 王道考研
mp3: 
cover: img/dijsktra.png
---


# 关于Dijkstra算法

✔重要

## 1.基本原理

假设它的起点是 a ，要求它到各点的最短距离

Dijkstra 思路是维护一个集合 s ，集合内的点是已经确定最短路的点，可以视为一个大整体，每次操作找出与集合相邻的点中距离起点最近的点加入集合中，并确定它的最短路为它的上家的最短路+该边权值，存在 dis 中；

形成类似于：dis=[∞，∞，∞，∞，∞]，其中∞表示不可达；s=[a,b,c,d,e]

✨每次选择离“整体”最近的一个点加入s，此处注意整体的概念，是所有已有点连成的一个图；

先用邻接矩阵存储数据，考虑采用一个二重循环，每次寻找出距离集合最近的一个点，然后数组标记它已经加入集合，然后在用当前点对不在集合中的点进行松弛，进行 n*n* 次，整个操作就完成了（此处代码中默认起点是1）

```c
void dijkstra()
{
    memset(dis,127/3,sizeof(dis));//初始化
    v[1]=1;
    dis[1]=0;
    for(int i=1;i<=n;++i)
    {
        int k=0;
        for(int j=1;j<=n;++j)//找出距离最近的点
            if(!v[j]&&(k==0||dis[j]<dis[k]))
                k=j;
        v[k]=1;//加入集合
        for(int j=1;j<=n;++j)//松弛
            if(!v[j]&&dis[k]+a[k][j]<dis[j])
                dis[j]=dis[k]+a[k][j];
    }
}

```

```c
#参考代码2：
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define X 10000
#define VertexNum  7  //实际上共有六个顶点（1---6）
#define EdgeNum  9

int Graph[VertexNum][VertexNum] =
//0  1  2  3  4  5  6
{ X, X, X, X, X, X, X,  //0
  X, X, 6, 3, X, X, X,  //1
  X, X, X, X, 5, X, X,  //2
  X, X, 2, X, 3, 4, X,  //3
  X, X, X, X, X, X, 3,  //4
  X, X, X, X, 2, X, 5,  //5
  X, X, X, X, X, X, X   //6
};

int Visited[VertexNum];
int path[VertexNum];
int Distance[VertexNum];

void Dijkstra(int Begin)
{
  int MinEdge, Vertex, i,j, Edges;
  Edges = 1;
  Visited[Begin] = 1;
  for (i = 1; i<VertexNum; i++) Distance[i] = Graph[Begin][i];

  Distance[Begin] = 0;
  printf("     1  2  3  4  5  6\\n");
  printf("-----------------------------------\\n");
  printf("s:%d", Edges);
  for( i=1; i<VertexNum; i++)
  if (Distance[i] == X) printf("  *"); else printf("%3d",Distance[i]);
  printf("\\n");
  while( Edges<VertexNum-1)
  {
    Edges++; MinEdge = X;
    for(j=1; j<VertexNum; j++)
    if (Visited[j]==0 && MinEdge > Distance[j] )
    {
 Vertex = j; MinEdge = Distance[j];
    }
    Visited[Vertex] = 1;
    printf("s:%d",Edges);
    for(j=1; j<VertexNum; j++)
    {
      if (Visited[j] == 0 && Distance[Vertex] + Graph[Vertex][j] <Distance[j])
      {   Distance[j] = Distance[Vertex] + Graph[Vertex][j];
   path[j] = Vertex;
      }
      //printf("%6d",Distance[j]);
       if (Distance[j] == X) printf("  *"); else printf("%3d",Distance[j]);
    }
    printf("\\n");
  }
}

void main()
{
  
  int i;
  int k;
 // clrscr();
  for(i=0; i<VertexNum; i++) { Visited[i] = 0;  path[i] = 1;}
  Dijkstra(1);
  printf("\\n\\nAll Path-------------------------\\n");


  for(i=2; i<VertexNum; i++) //printf("%5d",Visited[i]);
  {
     printf("[%d] ",Distance[i]);
     k = i;
     do
     {
       printf("%d<--",k);
       k  = path[k];
     } while (k!=1);
     printf("1 \\n");
  }
}
```

