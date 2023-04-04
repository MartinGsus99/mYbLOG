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
        SElemType DATA[MAXSIZE]={15,13,45,78,956,4512,545,12,10};
        T.elem=DATA;
        T.length=9;
        index=SearchBin(T);
        if(index==-1)
        {
            printf("No such a data.\n");
        }
}













