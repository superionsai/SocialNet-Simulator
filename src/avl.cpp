#include "avl.hpp"
#include <algorithm>
using namespace std;

int height(AVLNode* n){ return n ? n->height : 0; }
void update(AVLNode* n){ if(n) n->height = 1 + max(height(n->left), height(n->right)); }

AVLNode* rotate_right(AVLNode* y){
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}
AVLNode* rotate_left(AVLNode* x){
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

AVLNode* insert(AVLNode* node, const Post &p){
    if(!node) return new AVLNode(p);
    if(p.ts < node->post.ts) node->left = insert(node->left, p);
    else node->right = insert(node->right, p);
    update(node);
    int bf = height(node->left) - height(node->right);
    if(bf > 1 && p.ts < node->left->post.ts) return rotate_right(node);
    if(bf < -1 && p.ts >= node->right->post.ts) return rotate_left(node);
    if(bf > 1 && p.ts >= node->left->post.ts){
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if(bf < -1 && p.ts < node->right->post.ts){
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

void collect_recent(AVLNode* node, vector<Post> &out, int N){
    if(!node) return;
    if(N != -1 && (int)out.size() >= N) return;
    collect_recent(node->right, out, N);
    if(N != -1 && (int)out.size() >= N) return;
    out.push_back(node->post);
    if(N != -1 && (int)out.size() >= N) return;
    collect_recent(node->left, out, N);
}

void free(AVLNode* node){
    if(!node) return;
    free(node->left);
    free(node->right);
    delete node;
}
