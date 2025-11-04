#pragma once
#include <string>
#include <vector>

struct Post {
    long long ts;
    std::string content;
    Post(long long t=0, const std::string &c=""): ts(t), content(c) {}
};

struct AVLNode {
    Post post;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode(const Post &p): post(p), left(nullptr), right(nullptr), height(1) {}
};

int avl_height(AVLNode* n);
void avl_update(AVLNode* n);
AVLNode* avl_rotate_right(AVLNode* y);
AVLNode* avl_rotate_left(AVLNode* x);
AVLNode* avl_insert(AVLNode* node, const Post &p);
void avl_collect_recent(AVLNode* node, std::vector<Post> &out, int N);
void avl_free(AVLNode* node);
