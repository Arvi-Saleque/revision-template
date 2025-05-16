// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C

/*
sometimes i need to modify the find() function
first of all add all expreinece as team[u]
then when join() make self[v] = team[v] - team[u]
so for v the ans still team[v] = self[v] + team[u]
and when we find some other parents 
then the added points add to all players of a team 
so we do self[v] += self[p] so here self[p] 
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 

struct DSU {
    vector<ll> par, rank, sz, self, team;
    int n;
    DSU(int n) : n(n), par(n + 1), rank(n + 1, 0), sz(n + 1, 1), self(n + 1, 0), team(n + 1, 0) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int v) {                      // path-compression + offset update
        if (par[v] == v) return v;
        int p = par[v];
        par[v] = find(p);
        self[v] += self[p];                // accumulate the shift while climbing
        return par[v];
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    int get_size(int v) {
        return sz[find(v)];
    }
    int count() {
        return n; 
    }
    ll get_ans(int u) {
        int p = find(u);
        return team[p] + self[u];
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return;
        n--;
        if (rank[v] > rank[u]) swap(u, v);
        par[v] = u;
        self[v] = team[v] - team[u];
        sz[u] += sz[v];
        if (rank[u] == rank[v]) rank[u]++;
        // u is the parent;
    }
};
 
void solve() {
    int n, q;
    cin >> n >> q;
    DSU obj(n);
    while(q--) {
        string s; cin >> s;
        if(s[0] == 'a') {
            int x, v;
            cin >> x >> v;
            obj.team[obj.find(x)] += v;
        }
        else if(s[0] == 'j') {
            int u, v;
            cin >> u >> v;
            obj.join(u, v);
        }
        else {
            int x; cin >> x;
            cout << obj.get_ans(x) << "\n";
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
