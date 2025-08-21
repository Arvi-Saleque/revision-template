// http://judge.yosupo.jp/problem/eertree

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 10001, mod = 998244353;
const double eps = 1e-9;
struct palindromic_tree{
    struct node {
        int len, link, par, cursz;
        array<int, 26> next;
        node(int l = 0) : len(l), link(0), par(0), cursz(0) {
            next.fill(-1);
        }
    };
    string s;
    vector<node> t;
    int last;
    palindromic_tree(){}
    palindromic_tree(string _s) {
        t.clear();
        t.push_back(node(-1));
        t[0].cursz = 0;
        t.push_back(node(0));
        t[1].cursz = 1;
        t[0].link = 0;
        t[1].link = 0;
        last = 1;
        s = _s;
    }
    int getSufflink(int u, int i) {
        while(1) {
            int idx = i - 1 - t[u].len;
            if(idx >= 0 && s[idx] == s[i]) return u;
            u = t[u].link;
        }
    }
    int add(int i) {
        int u = getSufflink(last, i);
        int c = s[i] - 'a';
        if(t[u].next[c] != -1) {
            last = t[u].next[c];
            return 0;
        }
        node nv(t[u].len + 2);
        t.push_back(nv);
        int v = t.size() - 1;
        t[u].next[c] = v;
        t[v].cursz = t.size() - 1;
        t[v].par = t[u].cursz - 1;
        if(t[v].len == 1) {
            t[v].link = 1;
        }
        else {
            int w = t[u].link;
            w = getSufflink(w, i);
            t[v].link = t[w].next[c];
        }
        last = v;
        return 1;
    }
};
void solve() {
    string s; cin >> s;
    int n = s.size();
    palindromic_tree tree(s);
    vector<int> ans(n + 1);
    for(int i = 0; i < s.size(); i++) {
        tree.add(i);
        ans[i + 1] = tree.t[tree.last].cursz - 1;
    }
    cout << tree.t.size() - 2 << "\n";
    for(int i = 1; i <= tree.t.size() - 2; i++) {
        cout << tree.t[i + 1].par << " " << tree.t[tree.t[i + 1].link].cursz - 1 << "\n";
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
