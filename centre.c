#include <stdio.h>
#include <stdlib.h>
// 问题：数字：a[] 6181924013 
// 把 a[0]的数放中心 小放左 大方右
// 思想：temp=a[0] count=0
        //  从左到右找比六大的数
        //  从右到左找比六小的数
        //  找到后两数交换 使得小数在左边 大数字在右
        //  数有几个小于六的数 是⑦最后一个与a[0]的6交换
void print(int a[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d" ,a[i]);
    }
}

void swap(int *x, int *y) {
    int temp = *y;
    *y = *x;
    *x = temp;
}

void move(int a[],int n){
    int i=0,j=n-1;
    while(i<j){
        while(a[i]<=6){
            i++;
        }
        while(a[j]>=6){
            j--;
        }
        if(i>j) break;
        swap(&a[i],&a[j]);
        print(a,n);
        printf("\n");
    }
}
int count(int a[],int n){
    int i,count=0;
    for(i=0;i<n;i++){
        if(a[i]<6) count++; 
    }
    return count;
}

int main(){
    int n =10;
    int a[]={6,1,8,1,9,2,4,0,1,3};
     int temp=a[0]; int count1=0;
	  move(a,n);
    count1=count(a,n);
    a[0]=a[count1];
    a[count1]=temp;
    print(a,n);
    printf("\n");
    system("pause");
   }