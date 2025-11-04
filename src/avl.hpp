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

int height(AVLNode* n);
void update(AVLNode* n);
AVLNode* rotate_right(AVLNode* y);
AVLNode* rotate_left(AVLNode* x);
AVLNode* insert(AVLNode* node, const Post &p);
void collect_recent(AVLNode* node, std::vector<Post> &out, int N);
void free(AVLNode* node);
