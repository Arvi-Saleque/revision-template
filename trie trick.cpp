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

// https://www.spoj.com/problems/SUBXOR/

/*
count how many subarray Xor < k
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 
 
struct Trie {
    const int B = 20;
    struct node { // 1 based
        node *child[2];
        int cnt;
        node() {
            child[0] = child[1] = 0;
            cnt = 0;
        }
    } *root;
    
    Trie () {
        root = new node();
    }

    void insert(int x) {
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(!cur->child[id]) cur->child[id] = new node();
            cur = cur->child[id];
            cur->cnt++;
        }
    }

    ll countLess(int y, int k) {
        auto cur = root;
        ll ans = 0;
        for(int i = B - 1; i >= 0 && cur; i--) {
            int yb = (y >> i) & 1;
            int kb = (k >> i) & 1;
            if(kb == 1) {
                if(cur->child[yb]) {
                    ans += cur->child[yb]->cnt;
                }
                cur = cur->child[!yb];
            }
            else {
                cur = cur->child[yb];
            }
        }
        return ans;
    }

};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    ll ans = 0;
    int pref = 0;
    Trie trie;
    trie.insert(0);
    for(auto x : v) {
        pref ^= x;
        ans += trie.countLess(pref, k);
        trie.insert(pref);
    }
    cout << ans << "\n";
}  
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": " << "\n";
        solve();
    }
} 


// https://vjudge.net/problem/CSAcademy-xor-submatrix

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 
 
struct Trie {
    const int B = 29;
    struct node { // 1 based
        node *child[2];
        node() {
            child[0] = child[1] = 0;
        }
    } *root;
    
    Trie () {
        root = new node();
    }

    void insert(int x) {
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(!cur->child[id]) cur->child[id] = new node();
            cur = cur->child[id];
        }
    }

    int get_max(int x) {
        auto cur = root;
        int ans = 0;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(cur->child[!id]) {
                ans += (1 << i);
                cur = cur->child[!id];
            }
            else if(cur->child[id]){
                cur = cur->child[id];
            }
            else break;
        }
        return ans;
    }

    void clear(node *cur) {
        if(!cur) return;
        for(int i = 0; i < 2; i++) {
            if(cur->child[i]) clear(cur->child[i]);
        }
        delete(cur);
    }

    ~Trie() {
        clear(root);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1), u(m + 1);
    vector<int> prev(n + 1), preu(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        prev[i] = prev[i - 1] ^ v[i];
    }
    for(int j = 1; j <= m; j++) {
        cin >> u[j];
        preu[j] = preu[j - 1] ^ u[j];
    }

    int ans = 0;
    vector<int> rowodd, colodd;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            int val = prev[j] ^ prev[i - 1];
            if((j - i + 1) & 1) {
                rowodd.push_back(val);
            }
            else {
                ans = max(ans, val);
            }
        }
    }
    for(int i = 1; i <= m; i++) {
        for(int j = i; j <= m; j++) {
            int val = preu[j] ^ preu[i - 1];
            if((j - i + 1) & 1) {
                colodd.push_back(val);
            }
            else {
                ans = max(ans, val);
            }
        }
    }
    Trie trie;
    for(auto x : rowodd) {
        trie.insert(x);
    }
    for(auto x : colodd) {
        ans = max(ans, trie.get_max(x));
    }
    cout << ans << "\n";
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
