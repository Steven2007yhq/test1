#include<bits/stdc++.h>
using namespace std;
int vec[10];
int e;
int partition(int vec[],int low,int high){
    int u=vec[low];
    while(low<high){
        while(low<high&&vec[high]>u){high--;}
        vec[low]=vec[high];
        while(low<high&&vec[low]<=u){low++;}
        vec[high]=vec[low];
    }
    vec[low]=u;
    return low;
}
void Qsort(int vec[],int left,int right){
    if(left<right){
        e=partition(vec,left,right);
        Qsort(vec,left,e-1);
        Qsort(vec,e+1,right);
    }
}
void Quicksort(){
    Qsort(vec,0,9);
}

int main(){
    for(int i=0;i<=9;i++){
        scanf("%d",&vec[i]);
    }
    Quicksort();
    for(int i=0;i<=9;i++){
        printf("%d\t",vec[i]);
    }
}

