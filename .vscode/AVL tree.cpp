#include<bits/stdc++.h>
using namespace std;

struct node{
    node* left;
    node* right;
    node* parent;
    int data;
    int left_depth;  
    int right_depth;  


    node(int num=0): left(NULL),right(NULL),parent(NULL),data(num),left_depth(0),right_depth(0){}
};


int getDepth(node* n) {
    if(!n) return 0;
    return 1 + max(n->left_depth, n->right_depth);
}


node* rightRotate(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    if(T2) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;


    y->left_depth = getDepth(y->left);
    y->right_depth = getDepth(y->right);
    x->left_depth = getDepth(x->left);
    x->right_depth = getDepth(x->right);

    return x;
}


node* leftRotate(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    if(T2) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    // 更新深度！
    x->left_depth = getDepth(x->left);
    x->right_depth = getDepth(x->right);
    y->left_depth = getDepth(y->left);
    y->right_depth = getDepth(y->right);

    return y;
}


node* insert(node* root, int val) {
    // 1. BST 插入
    if(!root) return new node(val);

    if(val < root->data) {
        root->left = insert(root->left, val);
        root->left->parent = root;
    } else if(val > root->data) {
        root->right = insert(root->right, val);
        root->right->parent = root;
    } else {
        return root; 
    }

    root->left_depth = getDepth(root->left);
    root->right_depth = getDepth(root->right);


    int balance = root->left_depth - root->right_depth;


    if(balance > 1 && val < root->left->data)
        return rightRotate(root);

    if(balance < -1 && val > root->right->data)
        return leftRotate(root);

    if(balance > 1 && val > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance < -1 && val < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
node* getMinValueNode(node* root) {
    node* current = root;
    while(current->left != NULL)
        current = current->left;
    return current;
}
node* deleteNode(node* root, int key) {

    if(!root) return root;

    if(key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if((root->left == NULL) || (root->right == NULL)) {
            node* temp = root->left ? root->left : root->right;
            if(temp == NULL) {
                temp = root;
                root = NULL;
            } else {
            
                *root = *temp;
                if(temp->left) temp->left->parent = root;
                if(temp->right) temp->right->parent = root;
            }
            delete temp;
        } else {
        
            node* temp = getMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if(!root) return root;

    root->left_depth = getDepth(root->left);
    root->right_depth = getDepth(root->right);


    int balance = root->left_depth - root->right_depth;
    if(balance > 1 && (root->left ? (root->left->left_depth - root->left->right_depth) >= 0 : 0))
        return rightRotate(root);

    if(balance > 1 && (root->left ? (root->left->left_depth - root->left->right_depth) < 0 : 0)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    if(balance < -1 && (root->right ? (root->right->left_depth - root->right->right_depth) <= 0 : 0))
        return leftRotate(root);

    if(balance < -1 && (root->right ? (root->right->left_depth - root->right->right_depth) > 0 : 0)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
void levelOrder(node* root) {
    if(!root) return;
    queue<node*> q;
    q.push(root);
    while(!q.empty()) {
        node* current = q.front();
        q.pop();
        cout << current->data << " ";
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
    }
    cout << endl;
}
void inorder(node* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
  
int main() {
    node* root = NULL;
    int N = 15;
    cout << "请输入15个数字：\n";
    while(N--) {
        int a;
        cin >> a;
        root = insert(root, a);
        cout << "插入后中序: ";
        inorder(root);
     
        cout << "------------------------\n";
    }
    vector<int> del_keys = {20, 60, 30, 80};
    for(int key : del_keys) {
        cout << "\n删除节点 " << key << " 后，层序遍历结果: ";
        root = deleteNode(root, key);
        levelOrder(root);
        cout << "\n------------------------\n";
    }

    return 0;
}