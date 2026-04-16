

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
         Link<Elem> * next;
         Link(const Elem& item,Link<Elem> * nextval = NULL){element = item;next = nextval;}
         Link(Link<Elem> * nextval=NULL){next = nextval;}
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
          llist(){init();}
          ~llist(){removeall();}
          
          bool getvalue(Elem &e)const{
                if(curr->next==NULL)return false;
                e=curr->next->element;
                return true;
          }
          Link<Elem> * locate(Elem e){
              Link<Elem> * temp=head->next;
              while(temp!=NULL && temp->element!=e){
                temp=temp->next;
              }
              return temp;
          }
          bool isempty(){return (head->next==NULL);}
          bool setposition(int pos){
            curr=head;
            for(int i=1;i<=pos && curr!=NULL;i++){
              curr=curr->next;
            }
            return curr!=NULL;
          }
          bool insert(const Elem& x){
             Link<Elem>* s=new Link<Elem>(x);
             if(!s){
                cout<<"空间分配失败"<<endl;
                return false;
             }
             s->next=curr->next;
             curr->next=s;
             if(curr==tail){
                 tail=s;
             }
             return true;
          }
          bool remove(Elem &e){
            if(curr->next==NULL){
                return false;
            }
            Link<Elem> * q=curr->next;
            curr->next=q->next;
            e=q->element;
            if(q==tail){
                tail=curr;
            }
            delete q;
            return true;
          }
          void clear(){removeall();init();}
          void print()const{
              Link<Elem> * temp=head->next;
              while(temp!=NULL){
                  cout<<temp->element<<endl;
                  temp=temp->next;
              }
          }
          void next(){
            if(curr->next!=NULL){
                 curr=curr->next;
            }
          }
          void prev(){
            if(curr!=head){
                Link<Elem> * temp=head;
                while(temp!=NULL && temp->next!=curr){
                    temp=temp->next;
                }
                curr=temp;
            }
          }
};

int main() {
    llist<int> list;
    
    // 测试插入
    cout << "Testing insert..." << endl;
    for (int i = 1; i <= 5; i++) {
        list.insert(i);
    }
    
    // 测试打印
    cout << "List contents after insert: " << endl;
    list.print();
    
    // 测试获取值
    int val;
    list.setposition(0);
    if (list.getvalue(val)) {
        cout << "Value at position 0: " << val << endl;
    }
    
    // 测试移除
    cout << "Testing remove..." << endl;
    list.setposition(2);
    if (list.remove(val)) {
        cout << "Removed value: " << val << endl;
    }
    
    // 测试打印
    cout << "List contents after remove: " << endl;
    list.print();
    
    // 测试清空
    cout << "Testing clear..." << endl;
    list.clear();
    cout << "Is list empty? " << (list.isempty() ? "Yes" : "No") << endl;
    
    return 0;
}