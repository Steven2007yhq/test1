#include<bits/stdc++.h>
using namespace std;
template<class Elem>class List{
    public:
           virtual void clear()=0;
           virtual bool insert(const Elem&)=0;
           virtual bool remove(Elem&)=0;
           virtual void next()=0;
           virtual void prev()=0;
           virtual bool setposition(int pos)=0;
           virtual bool getvalue(Elem&)const=0;
           virtual bool isempty()=0;
           virtual void print()const=0;

};
template<class Elem> class Link{
    public:
         Elem element;
         Link * next;
         Link(const Elem& item,Link * nextval = NULL){element = item;next = nextval;}
         Link(Link * nextval=NULL){next = nextval;}
};
template<class Elem>class llist:public List<Elem>{
    private:
          Link<Elem> * head;
          Link<Elem> * tail;
          Link<Elem> * curr;
          void init(){
             curr=tail=head=new Link<Elem>;
          }
          void removeall(){
              while(head!=NULL){
                  curr=head;
                  head=head->next;
                  delete curr;
              }
          }
    public:
          LList(){init();}
          ~LLink(){removeall();}
          
          bool getvalue(Elem &e){
                if(head->next==NULL)return false;
                e=curr->element;
                return true;
          }
          Link * locate(Elem e){
              curr=head;
              while(curr->element!=e){
                curr++;
              }
              return curr;
          }
          bool isempty(){return (head->next==NULL);}
          bool setposition(int pos){
            curr=head;
            for(int i=1;i<=pos;i++){
              curr++;
            }
            return true;
          }
          bool insert(Elem x){
             Link* s=new Link;
             if(!s){
                cout<<"空间分配失败"<<endl;
                return false;
             }
             s->element=x;
             s->next=curr->next;
             curr->next=s;
             return true;


          }
          bool remove(Elem &e){
            if(curr->next==NULL){
                return false;
            }
            Link * q=curr->next;
            curr->next=q->next;
            e=q->element;
            delete q;
            return true;
          }
          void clear(){removeall();init();}
          void print(){
              while(curr->next!=NULL){
                  cout<<curr->element<<endl;
                  curr++;
              }
          }
          void next(){
            if(curr->next!=NULL){
                 curr++;
            }
         void prev(){
            if(curr->next!=NULL){
                curr--;
            }
         }

          };
};