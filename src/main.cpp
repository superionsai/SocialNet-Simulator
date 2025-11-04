#include <bits/stdc++.h>
#include "socialnet.hpp"
using namespace std;

bool DEBUG_MODE = false;
void debug(const string &msg) {
    if (DEBUG_MODE) cout << "[DEBUG] " << msg << "\n";
}

vector<string> split_keep_quotes(const string &line) {
    vector<string> out;
    string cur;
    bool inq = false;
    for (char c : line) {
        if (c == '"') {
            inq = !inq;
            cur.push_back(c);
        } else if (isspace((unsigned char)c) && !inq) {
            if (!cur.empty()) { out.push_back(cur); cur.clear(); }
        } else cur.push_back(c);
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

string strip_quotes(const string &s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SocialNet sn;
    cout << "Welcome to SocialNet!\n";
    cout << "Type commands below. Type EXIT to quit.\n\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        if (line == "EXIT" || line == "exit") {
            cout << "Goodbye.\n";
            break;
        }

        auto toks = split_keep_quotes(line);
        if (toks.empty()) continue;

        if (toks[0] == "DEBUG" && toks.size() >= 2) {
            string mode = toks[1];
            if (mode == "ON" || mode == "on") {
                DEBUG_MODE = true;
                cout << "Debug mode enabled.\n";
            } else if (mode == "OFF" || mode == "off") {
                DEBUG_MODE = false;
                cout << "Debug mode disabled.\n";
            } else {
                cout << "Usage: DEBUG ON / DEBUG OFF\n";
            }
            continue;
        }

        if (toks.size() >= 3 && toks[0] == "ADD" && toks[1] == "USER") {
            bool ok = sn.add_user(toks[2]);
            if (ok) cout << "User '" << toks[2] << "' added.\n";
            else cout << "Failed to add user.\n";
        }

        else if (toks.size() >= 4 && toks[0] == "ADD" && toks[1] == "FRIEND") {
            bool ok = sn.add_friend(toks[2], toks[3]);
            if (ok) cout << "Friendship created between '" << toks[2] << "' and '" << toks[3] << "'.\n";
            else cout << "Failed to add friend.\n";
        }

        else if (toks.size() >= 3 && toks[0] == "LIST" && toks[1] == "FRIENDS") {
            auto L = sn.list_friends(toks[2]);
            if (L.empty()) cout << "No friends found or user does not exist.\n";
            else {
                cout << "Friends of '" << toks[2] << "':\n";
                for (auto &s : L) cout << "  " << s << "\n";
            }
        }

        else if (toks.size() >= 4 && toks[0] == "SUGGEST" && toks[1] == "FRIENDS") {
            int N = 0;
            try { N = stoi(toks[3]); } catch (...) { N = 0; }
            auto L = sn.suggest_friends(toks[2], N);
            if (L.empty()) cout << "No suggestions available.\n";
            else {
                cout << "Suggested friends for '" << toks[2] << "':\n";
                for (auto &s : L) cout << "  " << s << "\n";
            }
        }

        else if (toks.size() >= 5 && toks[0] == "DEGREES" && toks[1] == "OF" && toks[2] == "SEPARATION") {
            int d = sn.degrees_of_separation(toks[3], toks[4]);
            cout << d << "\n";
        }

        else if (toks.size() >= 4 && toks[0] == "ADD" && toks[1] == "POST") {
            string quoted;
            for (size_t i = 3; i < toks.size(); ++i) {
                if (toks[i].front() == '"') {
                    quoted = toks[i];
                    if (toks[i].back() != '"') {
                        for (size_t j = i + 1; j < toks.size(); ++j) {
                            quoted += " " + toks[j];
                            if (toks[j].back() == '"') break;
                        }
                    }
                    break;
                }
            }
            string content = strip_quotes(quoted);
            bool ok = sn.add_post(toks[2], content);
            if (ok) cout << "Post added for '" << toks[2] << "'.\n";
            else cout << "Failed to add post.\n";
        }

        else if (toks.size() >= 4 && toks[0] == "OUTPUT" && toks[1] == "POSTS") {
            int N = 0;
            try { N = stoi(toks[3]); } catch (...) { N = -1; }
            auto posts = sn.output_posts(toks[2], N);
            if (posts.empty()) cout << "No posts found.\n";
            else {
                cout << "Posts for '" << toks[2] << "':\n";
                for (auto &p : posts) cout << "  " << p.content << "\n";
            }
        }

        else {
            cout << "Unknown or malformed command.\n";
        }
    }
    return 0;
}
