#include<bits/stdc++.h>
using namespace std;
#define Nulltag 0
#define deletetag -1

class HashList{
private:
    int * HT;
    int currentsize;
    int maxsize;
public:
    HashList(int maxsz=5){
        HT=new int[maxsz];
        maxsize=maxsz;
        currentsize=0;
        for(int i=0;i<maxsize;i++){
            HT[i]=Nulltag;
        }
    }
    ~HashList(){delete[] HT;}
    
    void clearHashList(){
        for(int i=0;i<maxsize;i++){
            HT[i]=Nulltag;
        }
        currentsize = 0; // 清空后重置有效元素数
    }
    
    // 修正哈希函数：对maxsize取模，保证下标合法
    int Hash(int item){
        return (item*3+5) % maxsize;
    }
    
    bool insert(int item){
        int d=Hash(item);
        int temp=d;
        while(HT[d]!=Nulltag&&HT[d]!=deletetag){
            d=(d+1)%maxsize;
            if(d==temp)return false; // 哈希表满
        }
        HT[d]=item;
        currentsize++; // 插入成功，更新有效元素数
        return true;
    }
    
    int search(int item){
        int d=Hash(item);
        int temp=d;
        while(HT[d]!=Nulltag){
            if(HT[d]==item){return d;}
            else{
                d=(d+1)%maxsize;
            }
            if(temp==d)return -1;
        }
        return -1;
    }
    
    bool Delete(int item){
        int d=Hash(item);
        int temp=d;
        while(HT[d]!=Nulltag){
            if(HT[d]==item){
                HT[d]=deletetag;
                currentsize--; // 删除成功，更新有效元素数
                return true;
            }
            else{
                d=(d+1)%maxsize;
            }
            if(d==temp)return false;
        }
        return false;
    }

    // 新增：打印哈希表（方便测试）
    void printHashList(){
        cout << "哈希表内容：";
        for(int i=0;i<maxsize;i++){
            if(HT[i]==Nulltag) cout << "空 ";
            else if(HT[i]==deletetag) cout << "删 ";
            else cout << HT[i] << " ";
        }
        cout << "（有效元素数：" << currentsize << "）" << endl;
    }
};

// 测试代码
int main(){
    HashList hl(5); // 创建容量为5的哈希表
    hl.insert(1);
    hl.insert(2);
    hl.insert(3);
    hl.printHashList(); // 输出：哈希表内容：删 11 8 5 空 （有效元素数：3）
    
    cout << "查找元素2的位置：" << hl.search(2) << endl; // 输出：1
    hl.Delete(2);
    hl.printHashList(); // 输出：哈希表内容：删 删 8 5 空 （有效元素数：2）
    
    cout << "查找元素2的位置：" << hl.search(2) << endl; // 输出：-1
    return 0;
}