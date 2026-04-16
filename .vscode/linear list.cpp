#include<bits/stdc++.h>
using namespace std;
template<class Elem>class List{
    public:
           virtual void clear()=0;
           virtual bool insert(const Elem&)=0;
           virtual bool append(const Elem&)=0;
           virtual bool remove(Elem&)=0;
           virtual void next()=0;
           virtual void prev()=0;
           virtual bool setposition(int pos)=0;
           virtual bool getvalue(Elem&)const=0;
           virtual bool isempty()=0;
           virtual bool isfull()=0;
           virtual void print()const=0;

};
template<class Elem>
class Alist:public List<Elem>{
      private:
             int maxsize;
             int listsize;
             int curr;
             Elem *listarray;
     public:
            Alist(int size=3){
                  maxsize=size;
                  listsize=curr=0;
                  listarray=new Elem[maxsize];
            }
            ~Alist(){delete[] listarray;}
            void clear(){listsize=curr=0;}
            void prev(){if(curr>0)curr--;}
            void next(){if(curr<listsize-1)curr++;}
            bool insert(const Elem& it){
                 if(listsize==maxsize)return false;
                 if((curr>listsize-1)||(curr<0)) return false;
                 for(int i=listsize-1;i>=curr;i--) listarray[i+1]=listarray[i];
                 listarray[curr]=it;
                 listsize++;
                 return true;
            }
            bool append(const Elem& it){
                if(listsize==maxsize){
                    return false;
                }
                listarray[listsize++]=it;
                return true;
            }
            bool remove(Elem& it){
                if(listsize==0)return false;
                if((curr<0)||(curr>=listsize))return false;
                it=listarray[curr];
                for(int i=curr+1;i<=listsize-1;i++)listarray[i-1]=listarray[i];
                listsize--;
                return true;
            }
            bool setposition(int pos){
                if((pos>=listsize)||(pos<0))return false;
                curr=pos;
                return true; 
            }
            bool getvalue(Elem& it)const{
                if(listsize>=maxsize){
                     return false;
                }
                if(curr>=listsize)return false;
                it=listarray[curr];
                return true;
            }           
            bool isempty(){
                if(listsize==0){
                    return true;
                }
                return false;
            }
            bool isfull(){
                if(listsize==maxsize){
                    return true;
                }
                return false;
            }
            void print()const{
                 for(int i=0;i<=listsize-1;i++){
                    cout<<listarray[i]<<endl;
                 }
            }
};
int main(){
       Alist<float> a1(4),a2;
       a1.append(34.8);
       a2.append(34.5);
       a1.append(3454.7);
       a2.append(3.5);
       a1.append(34.7);
       a2.append(4.5);
       if(a1.isfull()){
         a1.print();
       }
       if(a2.isfull()){
        a2.print();
       }
   
        return 0;
}