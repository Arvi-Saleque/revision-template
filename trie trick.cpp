// https://www.spoj.com/status/ns=34585389

/*
if you need dfs on trie
at first make the trie an uniqe tree
inserting an unique id on each node
then just treat as node of a tree
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 
 
class Trie {
public:
 
    class node { // 1 based
    public:
        node *child[27];
        int leaf, sz, id;
        node() {
            for(int i = 0; i < 27; i++) {
                child[i] = nullptr;
            }
            sz = 0;
            leaf = 0;
            id = 0;
        }
    } *root;
    
    vector<int> dis;
    int unqid = 1;

    Trie () {
        root = new node();

    }

    void insert(string s) {
        auto cur = root; 
        for(auto x : s) {
            int i = x - 'a' + 1; // 1-based
            if(!cur->child[i]) { 
                cur->child[i] = new node(); // edge dilam
            }
            cur = cur->child[i];
            cur->sz++; // new edge e ashalam ebar increment korbo 
            cur->id = unqid++;
        }
        cur->leaf++;
    }

    int set(node *cur) {
        dis[cur->id] = cur->leaf;
        for(int i = 1; i <= 26; i++) {
            if(cur->child[i]) {
                set(cur->child[i]);
                dis[cur->id] = max(dis[cur->id], dis[cur->child[i]->id]);
            }
        }
        return dis[cur->id];
    }

    pair<string, int> calc(string s) {
        node *cur = root;
        for(auto x : s) {
            int id = x - 'a' + 1;
            if(cur->child[id] == nullptr) return {"", -1};
            cur = cur->child[id];
        }
        pair<string, int> ans = {s, cur->leaf};
        while(1) {
            int node = -1, mx = ans.second;
            for(int i = 1; i <= 26; i++) {
                if(cur->child[i] && dis[cur->child[i]->id] > mx) {
                    mx = dis[cur->child[i]->id];
                    node = i;
                }
            }
            if(node == -1) break;
            cur = cur->child[node];
            ans.first.push_back((char)(node + 'a' - 1));
            ans.second = cur->leaf;
        }
        return ans;
    }
};
void solve() {
    int n;
    cin >> n;
    Trie mytrie;
    for(int i = 1; i <= n; i++) {
        string t; cin >> t;
        mytrie.insert(t);
    }
    mytrie.dis.assign(mytrie.unqid + 1, 0);
    mytrie.set(mytrie.root);
    int q; cin >> q;
    while(q--) {
        string s; 
        cin >> s;
        auto [ss, c] = mytrie.calc(s);
        if(c == -1) {
            cout << "-1\n";
        }
        else {
            cout << ss << " " << c << "\n";
        }
    }
}  
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": " << "\n";
        solve();
    }
} 
