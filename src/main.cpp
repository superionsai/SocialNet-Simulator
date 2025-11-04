#include <bits/stdc++.h>
#include "socialnet.hpp"
using namespace std;

string to_uppercase(string s) {
    string res;
    for (char &c : s)
        res += toupper(static_cast<unsigned char>(c));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SocialNet sn;
    cout << "Welcome to SocialNet. Type commands below (EXIT to quit):" << endl;

    string line;
    while (true) {
        cout << "> " << flush;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        stringstream ss(line);
        string cmd;
        ss >> cmd;
        cmd = to_uppercase(cmd);

        if (cmd == "EXIT") break;

        if (cmd == "ADD") {
            string type;
            ss >> type;
            type = to_uppercase(type);

            if (type == "USER") {
                string user;
                ss >> user;
                user = to_uppercase(user);
                if (sn.add_user(user))
                    cout << "User '" << user << "' added." << endl;
                else
                    cout << "Failed to add user." << endl;
            } 
            else if (type == "FRIEND") {
                string u1, u2;
                ss >> u1 >> u2;
                u1 = to_uppercase(u1);
                u2 = to_uppercase(u2);
                if (sn.add_friend(u1, u2))
                    cout << "Friendship created between '" << u1 << "' and '" << u2 << "'." << endl;
                else
                    cout << "Failed to add friendship." << endl;
            } 
            else if (type == "POST") {
                string user;
                ss >> user;
                user = to_uppercase(user);
                string rest;
                getline(ss, rest);
                size_t start = rest.find('"'), end = rest.rfind('"');
                string content = (start != string::npos && end != string::npos && end > start)
                                 ? rest.substr(start + 1, end - start - 1)
                                 : rest;
                if (sn.add_post(user, content))
                    cout << "Post added for '" << user << "'." << endl;
                else
                    cout << "Failed to add post." << endl;
            }
        } 
        else if (cmd == "LIST") {
            string what, user;
            ss >> what >> user;
            what = to_uppercase(what);
            user = to_uppercase(user);
            if (what == "FRIENDS") {
                auto friends = sn.list_friends(user);
                if (friends.empty()) cout << "No friends found or user not found." << endl;
                else {
                    cout << "Friends of '" << user << "':" << endl;
                    for (auto &f : friends) cout << f << endl;
                }
            }
        } 
        else if (cmd == "SUGGEST") {
            string what, user;
            int N;
            ss >> what >> user >> N;
            what = to_uppercase(what);
            user = to_uppercase(user);
            if (what == "FRIENDS") {
                auto sug = sn.suggest_friends(user, N);
                if (sug.empty()) cout << "No suggestions available." << endl;
                else {
                    cout << "Suggested friends for '" << user << "':" << endl;
                    for (auto &s : sug) cout << s << endl;
                }
            }
        } 
        else if (cmd == "DEGREES") {
            string of, sep, u1, u2;
            ss >> of >> sep >> u1 >> u2;
            if (to_uppercase(of)=="OF" && to_uppercase(sep)=="SEPARATION") {
                u1 = to_uppercase(u1);
                u2 = to_uppercase(u2);
                int d = sn.degrees_of_separation(u1, u2);
                cout << d << endl;
            }
            else {
                cout << "Unknown or malformed command." << endl;
            }
        } else if (cmd == "OUTPUT") {
            string what, user;
            int N;
            ss >> what >> user >> N;
            what = to_uppercase(what);
            user = to_uppercase(user);
            if (what == "POSTS") {
                auto posts = sn.output_posts(user, N);
                if (posts.empty()) cout << "No posts found or user not found." << endl;
                else {
                    cout << "Posts for '" << user << "':" << endl;
                    for (auto &p : posts) cout << p.content << endl;
                }
            }
        } else {
            cout << "Unknown or malformed command." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
