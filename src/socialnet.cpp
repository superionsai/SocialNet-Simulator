#include "socialnet.hpp"
#include <algorithm>
#include <queue>
#include <cctype>
using namespace std;

SocialNet::SocialNet(): global_ts(0) {}

SocialNet::~SocialNet(){
    for(auto &u: users)  free(u.posts);
}

string SocialNet::normalize(const string &s) const {
    string r;
    for(char c: s) if(!isspace((unsigned char)c) || !r.empty()) r.push_back(tolower((unsigned char)c));
    size_t st = 0;
    while(st < r.size() && isspace((unsigned char)r[st])) st++;
    size_t ed = r.size();
    while(ed > st && isspace((unsigned char)r[ed-1])) ed--;
    return r.substr(st, ed-st);
}

int SocialNet::get_id(const string &norm) const {
    auto it = name2id.find(norm);
    if(it == name2id.end()) return -1;
    return it->second;
}

bool SocialNet::add_user(const string &rawname){
    string n = normalize(rawname);
    if(n.empty()) return false;
    if(name2id.count(n)) return false;
    int id = users.size();
    users.emplace_back();
    users[id].name_lower = n;
    users[id].display_name = rawname;
    name2id[n] = id;
    adj.emplace_back();
    return true;
}

bool SocialNet::add_friend(const string &a, const string &b){
    string an = normalize(a), bn = normalize(b);
    if(!name2id.count(an) || !name2id.count(bn)) return false;
    int ia = name2id[an], ib = name2id[bn];
    if(ia==ib) return false;
    adj[ia].insert(ib);
    adj[ib].insert(ia);
    return true;
}

vector<string> SocialNet::list_friends(const string &rawname) const {
    vector<string> res;
    string n = normalize(rawname);
    int id = get_id(n);
    if(id == -1) return res;
    for(int v: adj[id]) res.push_back(users[v].display_name);
    sort(res.begin(), res.end(), [](const string &a, const string &b){
        string la=a, lb=b; 
        transform(la.begin(), la.end(), la.begin(), ::tolower); 
        transform(lb.begin(), lb.end(), lb.begin(), ::tolower);
        return la < lb;
    });
    return res;
}

vector<string> SocialNet::suggest_friends(const string &rawname, int N) const {
    vector<string> res;
    if(N==0) return res;
    string n = normalize(rawname);
    int id = get_id(n);
    if(id == -1) return res;
    unordered_map<int,int> mutual;
    for(int f: adj[id]){
        for(int fof: adj[f]){
            if(fof==id) continue;
            if(adj[id].count(fof)) continue;
            mutual[fof]++;
        }
    }
    vector<pair<int,int>> cand;
    for(auto &kv: mutual) cand.emplace_back(kv.first, kv.second);
    sort(cand.begin(), cand.end(), [&](const pair<int,int>&A, const pair<int,int>&B) {
        if(A.second != B.second) return A.second > B.second;
        string a = users[A.first].display_name, b = users[B.first].display_name;
        string la=a, lb=b; 
        transform(la.begin(), la.end(), la.begin(), ::tolower); 
        transform(lb.begin(), lb.end(), lb.begin(), ::tolower);
        return la < lb;
    });
    int limit = (N<0) ? (int)cand.size() : min((int)cand.size(), N);
    for(int i=0;i<limit;i++) res.push_back(users[cand[i].first].display_name);
    return res;
}

int SocialNet::degrees_of_separation(const string &a, const string &b) const {
    string an = normalize(a), bn = normalize(b);
    if(!name2id.count(an) || !name2id.count(bn)) return -1;
    int s = name2id.at(an), t = name2id.at(bn);
    if(s==t) return 0;
    vector<int> dist(users.size(), -1);
    queue<int> q;
    dist[s]=0; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v: adj[u]){
            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                if(v==t) return dist[v];
                q.push(v);
            }
        }
    }
    return -1;
}

bool SocialNet::add_post(const string &rawname, const string &content){
    std::string n = normalize(rawname);
    if(!name2id.count(n)) return false;
    int id = name2id.at(n);
    global_ts++;
    Post p(global_ts, content);
    users[id].posts =  insert(users[id].posts, p);
    return true;
}

vector<Post> SocialNet::output_posts(const string &rawname, int N) const {
    vector<Post> res;
    string n = normalize(rawname);
    if(!name2id.count(n)) return res;
    int id = name2id.at(n);
     collect_recent(users[id].posts, res, N);
    return res;
}
