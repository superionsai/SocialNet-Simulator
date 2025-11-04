#include "avl.hpp"
#include <algorithm>

int avl_height(AVLNode* n){ return n ? n->height : 0; }
void avl_update(AVLNode* n){ if(n) n->height = 1 + std::max(avl_height(n->left), avl_height(n->right)); }

AVLNode* avl_rotate_right(AVLNode* y){
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    avl_update(y);
    avl_update(x);
    return x;
}
AVLNode* avl_rotate_left(AVLNode* x){
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    avl_update(x);
    avl_update(y);
    return y;
}

AVLNode* avl_insert(AVLNode* node, const Post &p){
    if(!node) return new AVLNode(p);
    if(p.ts < node->post.ts) node->left = avl_insert(node->left, p);
    else node->right = avl_insert(node->right, p);
    avl_update(node);
    int bf = avl_height(node->left) - avl_height(node->right);
    if(bf > 1 && p.ts < node->left->post.ts) return avl_rotate_right(node);
    if(bf < -1 && p.ts >= node->right->post.ts) return avl_rotate_left(node);
    if(bf > 1 && p.ts >= node->left->post.ts){
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }
    if(bf < -1 && p.ts < node->right->post.ts){
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }
    return node;
}

void avl_collect_recent(AVLNode* node, std::vector<Post> &out, int N){
    if(!node) return;
    if(N != -1 && (int)out.size() >= N) return;
    avl_collect_recent(node->right, out, N);
    if(N != -1 && (int)out.size() >= N) return;
    out.push_back(node->post);
    if(N != -1 && (int)out.size() >= N) return;
    avl_collect_recent(node->left, out, N);
}

void avl_free(AVLNode* node){
    if(!node) return;
    avl_free(node->left);
    avl_free(node->right);
    delete node;
}
