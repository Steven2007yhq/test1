#include<bits/stdc++.h>
#define Maxno 5
using namespace std;

typedef struct{
    int row;
    int col;
    int element;

}Tritype;
typedef struct{
    int rno;
    int cno;
    int teno;
    Tritype data[Maxno];
}TMatrix;
int TransTMatrix(TMatrix Sm,TMatrix &St){
    int i,j,k;
    St.rno=Sm.cno;
    St.cno=Sm.rno;
    St.teno=Sm.teno;
    if(St.teno!=0){
        j=1;
        for(int i=1;i<=Sm.cno;i++){
            for(int k=1;k<=Sm.rno;k++){
                if(Sm.data[k].col==i){
                    St.data[j].row=Sm.data[k].col;
                    St.data[j].col=Sm.data[k].row;
                    St.data[j].element=Sm.data[k].element;
                    j++;
                }
              
            }
        }
    }
    return 0;

}
int main(){
    TMatrix a,t;
    a.cno=8;
    a.rno=9;
    a.teno=4;
    for(int i=1;i<=a.teno;i++){
        cin>>a.data[i].row>>a.data[i].col>>a.data[i].element;
    }
    TransTMatrix(a,t);
    for(int i=1;i<=t.teno;i++){
        cout<<"("<<t.data[i].row<<","<<t.data[i].col<<","<<t.data[i].element<<")  ";
    }

}
