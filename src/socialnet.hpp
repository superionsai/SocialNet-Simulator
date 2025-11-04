#pragma once
#include "avl.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct User {
    string name_lower;
    string display_name;
    AVLNode* posts;
    User(): posts(nullptr) {}
};

class SocialNet {
public:
    SocialNet();
    ~SocialNet();
    bool add_user(const string &rawname);
    bool add_friend(const string &a, const string &b);
    vector< string> list_friends(const string &rawname) const;
    vector< string> suggest_friends(const string &rawname, int N) const;
    int degrees_of_separation(const string &a, const string &b) const;
    bool add_post(const string &rawname, const string &content);
    vector<Post> output_posts(const string &rawname, int N) const;

private:
    string normalize(const string &s) const;
    int get_id(const string &norm) const;
    unordered_map<string,int> name2id;
    vector<User> users;
    vector< unordered_set<int>> adj;
    mutable long long global_ts;
};
