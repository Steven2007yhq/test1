#include<bits/stdc++.h>
using namespace std;

enum Tag{L,R};
template<class T> class Binarytree;

template<class T>
class Binarytreenode{
    friend class Binarytree<T>;

private:
    T data;
    Binarytreenode<T> *left;
    Binarytreenode<T> *right;
public:
    Binarytreenode(){
        data=0;
        left=right=NULL;
    }
    Binarytreenode(const T&ele){
        data=ele;
        left=right=NULL;
    }
    Binarytreenode(const T&ele,Binarytreenode<T>*l,Binarytreenode<T>*r){
        data=ele;
        left=l;
        right=r;
    }
    ~Binarytreenode(){};
    T value()const{
        return data;
    }
    Binarytreenode<T>& operator=(const Binarytreenode<T>&node){
        if (this != &node) {
            this->data = node.data;
            this->left = node.left;
            this->right = node.right;
        }
        return *this;
    }
    Binarytreenode<T> *leftchild()const{return left;}
    Binarytreenode<T> *rightchild()const{return right;}
    void setleftchild(Binarytreenode<T> *l){left=l;}
    void setrightchild(Binarytreenode<T> *r){right=r;}
    void setvalue(const T&val){data=val;}
    bool isleaf()const{
        return (left==NULL&&right==NULL);
    } 
};

template<class T>class StackNode{
public:
    Binarytreenode<T>*pointer;
    Tag tag;
};

template<class T>
class Binarytree{
protected:
    Binarytreenode<T>*root;
public:
    Binarytree(){root=NULL;}
    Binarytree(Binarytreenode<T>*r){
        root=r;
    }
    ~Binarytree(){deleteBinarytree(root);}
    
    bool isempty()const{
        return root==NULL;
    }
    
    void visit(const T&data){cout<<data<<" ";}
    
    Binarytreenode<T> *&Root(){return root;}
    
    Binarytreenode<T> *leftsibling(Binarytreenode<T>*current){
        return current->leftchild();
    }
    
    Binarytreenode<T> *rightsibling(Binarytreenode<T>*current){
        return current->rightchild();
    }
    
    void createtree(const T&data,Binarytree<T>&lefttree,Binarytree<T>&righttree){
        root=new Binarytreenode<T>(data);
        root->left=lefttree.Root();  // 修正：调用lefttree的Root()
        root->right=righttree.Root();// 修正：调用righttree的Root()
    }
    
    void createtree(Binarytreenode<T>*&r){
        T ch;
        cin>>ch;
        if(ch=='#'){r=NULL;}
        else{
            r=new Binarytreenode<T>(ch);
            createtree(r->left);
            createtree(r->right);
        }
    }

    void deleteBinarytree(Binarytreenode<T>*& root) {
        if (root == nullptr) {
            return;
        }
        deleteBinarytree(root->left);
        deleteBinarytree(root->right);
        delete root;
        root = nullptr;
    }

    void Preorder(Binarytreenode<T>*root){
        if(root==NULL){return ;}
        else{
            visit(root->value());
            Preorder(root->leftchild());
            Preorder(root->rightchild());
        }
    }

    void Inorder(Binarytreenode<T>*root){
        if(root==NULL){
            return;
        }
        else{
            Inorder(root->leftchild());
            visit(root->value());
            Inorder(root->rightchild());
        }
    }

    void Postorder(Binarytreenode<T>*root){
        if(root==NULL)return ;
        Postorder(root->leftchild());
        Postorder(root->rightchild());
        visit(root->value());
    }

    void PreorderwithoutRecusion(Binarytreenode<T>* root) {
        stack<Binarytreenode<T>*> tstack;
        Binarytreenode<T>* pointer = root;
        
        while (pointer || !tstack.empty()) {
            if (pointer) {
                visit(pointer->value());
                tstack.push(pointer);
                pointer = pointer->leftchild();
            } else {
                pointer = tstack.top();
                tstack.pop();
                pointer = pointer->rightchild();
            }
        }
    }
    
    void Inorderwithoutrecusion(Binarytreenode<T>* root) {
        stack<Binarytreenode<T>*> tstack;
        Binarytreenode<T>* pointer = root;
        
        while (pointer || !tstack.empty()) {
            if (pointer) {
                tstack.push(pointer);
                pointer = pointer->leftchild();
            } else {
                pointer = tstack.top();
                tstack.pop();
                visit(pointer->value());
                pointer = pointer->rightchild();
            }
        }
    }

    void Postorderwithoutrecusion(Binarytreenode<T> *root){
        stack<StackNode<T>>tstack;
        StackNode<T> Node;
        Binarytreenode<T>*pointer=root;
        do{
            while(pointer!=NULL){
                Node.pointer=pointer;
                Node.tag=L;
                tstack.push(Node);
                pointer=pointer->leftchild();
            }
            Node=tstack.top();
            tstack.pop();
            pointer=Node.pointer;
            if(Node.tag==R){
                visit(pointer->value());
                pointer=NULL;
            }
            else{
                Node.tag=R;
                tstack.push(Node);
                pointer=pointer->rightchild();
            }
        }while(!tstack.empty()||pointer);
    }

    void levelorder(Binarytreenode<T>*root){
        queue<Binarytreenode<T>*>tqueue;
        Binarytreenode<T>*pointer=root;
        if(pointer)tqueue.push(pointer);
        while(!tqueue.empty()){
            pointer=tqueue.front();
            tqueue.pop();
            visit(pointer->value());
            if(pointer->leftchild()!=NULL){
                tqueue.push(pointer->leftchild());
            }
            if(pointer->rightchild()!=NULL){
                tqueue.push(pointer->rightchild());
            }
        }
    }

    // ========== 新增：查找双亲节点的核心功能 ==========
    // 递归版：查找指定值节点的双亲节点
    Binarytreenode<T>* findParent(Binarytreenode<T>* currentRoot, const T& target) {
        // 终止条件1：空树，无父节点
        if (currentRoot == nullptr) {
            return nullptr;
        }
        
        // 终止条件2：当前节点的左/右孩子是目标节点，当前节点就是父节点
        if ((currentRoot->leftchild() != nullptr && currentRoot->leftchild()->value() == target) ||
            (currentRoot->rightchild() != nullptr && currentRoot->rightchild()->value() == target)) {
            return currentRoot;
        }
        
        // 递归查找左子树
        Binarytreenode<T>* leftParent = findParent(currentRoot->leftchild(), target);
        if (leftParent != nullptr) {
            return leftParent;
        }
        
        // 递归查找右子树
        Binarytreenode<T>* rightParent = findParent(currentRoot->rightchild(), target);
        return rightParent;
    }

    // 封装接口：对外提供的查找双亲节点方法（更友好）
    T findParentValue(const T& target) {
        // 特殊情况1：空树
        if (root == nullptr) {
            cout << "错误：二叉树为空！" << endl;
            return T(); // 返回默认值
        }
        
        // 特殊情况2：目标是根节点（无父节点）
        if (root->value() == target) {
            cout << "提示：" << target << " 是根节点，无父节点！" << endl;
            return T(); // 返回默认值
        }
        
        // 调用递归函数查找父节点
        Binarytreenode<T>* parentNode = findParent(root, target);
        
        // 特殊情况3：未找到目标节点
        if (parentNode == nullptr) {
            cout << "错误：未找到节点 " << target << "！" << endl;
            return T(); // 返回默认值
        }
        
        // 找到父节点，返回其值
        return parentNode->value();
    }
};
int main() {
    Binarytree<char> tree;
    Binarytreenode<char>* root = nullptr;
    
    cout << "请输入二叉树节点（#表示空节点，按先序顺序输入）：" << endl;
    tree.createtree(root);
    tree.Root() = root;
    
    cout << "前序遍历（递归）：";
    tree.Preorder(root);
    cout << endl;
    
    cout << "中序遍历（递归）：";
    tree.Inorder(root);
    cout << endl;
    
    cout << "后序遍历（递归）：";
    tree.Postorder(root);
    cout << endl;
    
    cout << "层序遍历：";
    tree.levelorder(root);
    cout << endl;

    // ========== 测试查找双亲节点功能 ==========
    char target;
    cout << "\n请输入要查找双亲的节点值：";
    cin >> target;
    
    char parentValue = tree.findParentValue(target);
    if (parentValue != 0) { // 排除默认值
        cout << "节点 " << target << " 的双亲节点是：" << parentValue << endl;
    }
    
    return 0;
}