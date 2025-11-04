#pragma once
#include "avl.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct User {
    std::string name_lower;
    std::string display_name;
    AVLNode* posts;
    User(): posts(nullptr) {}
};

class SocialNet {
public:
    SocialNet();
    ~SocialNet();
    bool add_user(const std::string &rawname);
    bool add_friend(const std::string &a, const std::string &b);
    std::vector<std::string> list_friends(const std::string &rawname) const;
    std::vector<std::string> suggest_friends(const std::string &rawname, int N) const;
    int degrees_of_separation(const std::string &a, const std::string &b) const;
    bool add_post(const std::string &rawname, const std::string &content);
    std::vector<Post> output_posts(const std::string &rawname, int N) const;

private:
    std::string normalize(const std::string &s) const;
    int get_id(const std::string &norm) const;
    std::unordered_map<std::string,int> name2id;
    std::vector<User> users;
    std::vector<std::unordered_set<int>> adj;
    mutable long long global_ts;
};
