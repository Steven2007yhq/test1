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
template<class Elem>class Dlink{
    public:
        Elem element;
        Dlink * prev;
        Dlink * next;
        Dlink(const Elem& it,Dlink*p=NULL,Dlink*n=NULL){
            element = it;
            prev=p;
            next=n;
        }
        Dlink(Dlink*p=NULL,Dlink*n=NULL){prev=p;next=n;}
        ~Dlink(){}
};
template <class Elem>class Dlist:
public List<Elem>{
    private:
       Dlink<Elem> *head, *tail, *curr;
    public:
       Dlist(){
          curr=tail=head=new Dlink<Elem>;


       }
       ~Dlist(){
        while(head!=NULL){
              curr=head;
              head=head->next;
              delete curr;
        }
       }
        bool insert(const Elem& x){
          Dlink<Elem> *nextptr,*newptr;
          nextptr=curr->next;
          newptr=new Dlink<Elem>(x,curr,nextptr);
          if(newptr==NULL)return false;
          curr->next=newptr;
          if(nextptr!=NULL){
              nextptr->prev=newptr;
          } else {
              tail=newptr; // 更新tail指针
          }
          return true;
       }
       bool remove(Elem& x){
         if(curr==NULL||curr==head||curr==tail){return false;} // 不能删除头节点
         Dlink<Elem> *temp=curr;
         curr->prev->next=curr->next;
         if(curr->next!=NULL){
             curr->next->prev=curr->prev;
             curr=curr->next; // 移动到下一个节点
         } else {
             curr=curr->prev; // 移动到前一个节点
             tail=curr; // 更新tail指针
         }
         x=temp->element;
         delete temp;
         return true;
       }
       void clear(){
           while(head->next!=NULL){
               curr=head->next;
               head->next=curr->next;
               if(curr->next!=NULL){
                   curr->next->prev=head;
               }
               delete curr;
           }
           curr=head;
       }
       void next(){
           if(curr->next!=NULL){
               curr=curr->next;
           }
       }
       void prev(){
           if(curr->prev!=NULL){
               curr=curr->prev;
           }
       }
       bool setposition(int pos){
           if(pos<0)return false;
           curr=head;
           for(int i=0;i<pos && curr->next!=NULL;i++){
               curr=curr->next;
           }
           return curr->next!=NULL;
       }
       bool getvalue(Elem& x)const{
           if(curr==NULL||head->next==NULL)return false;
           x=curr->next->element;
           return true;
       }
       bool isempty(){
           return head->next==NULL;
       }
       void print()const{
           Dlink<Elem> *temp=head->next;
           cout<<"[";
           while(temp!=NULL){
               cout<<temp->element;
               if(temp->next!=NULL)cout<<",";
               temp=temp->next;
           }
           cout<<"]"<<endl;
       }
};

int main(){
    Dlist<int> list;
    cout<<"=== 双向链表测试 ==="<<endl;
    
    cout<<"\n1. 测试插入功能:"<<endl;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.print();
    
    cout<<"\n2. 测试next()移动:"<<endl;
    list.setposition(0);
    cout<<"当前值: ";
    int val;
    list.getvalue(val);
    cout<<val<<endl;
    list.next();
    cout<<"next后: ";
    list.getvalue(val);
    cout<<val<<endl;
    
    cout<<"\n3. 测试prev()移动:"<<endl;
    list.prev();
    cout<<"prev后: ";
    list.getvalue(val);
    cout<<val<<endl;
    
    cout<<"\n4. 测试setposition(2):"<<endl;
    list.setposition(2);
    list.getvalue(val);
    cout<<"位置2的值: "<<val<<endl;
    
    cout<<"\n5. 测试isempty():"<<endl;
    cout<<"列表是否为空: "<<(list.isempty()?"是":"否")<<endl;
    
    cout<<"\n6. 测试remove():"<<endl;
    list.setposition(1);
    cout<<"删除前: ";
    list.print();
    list.remove(val);
    cout<<"删除的值: "<<val<<endl;
    cout<<"删除后: ";
    list.print();
    
    cout<<"\n7. 测试clear():"<<endl;
    list.clear();
    cout<<"清空后是否为空: "<<(list.isempty()?"是":"否")<<endl;
    list.print();
    
    cout<<"\n8. 测试string类型:"<<endl;
    Dlist<string> strList;
    strList.insert("hello");
    strList.insert("world");
    strList.insert("!");
    strList.print();
    
    cout<<"\n=== 所有测试完成 ==="<<endl;
    
    return 0;
}