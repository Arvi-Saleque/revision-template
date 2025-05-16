#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 

struct DSU {
    vector<ll> par, rank, sz, sum, elemwhichnode;
    int n, nextId;
    DSU(int n, int m)
        : par(n + m + 1),
          rank(n + m + 1, 0),
          sz(n + m + 1, 1),
          sum(n + m + 1),
          elemwhichnode(n + 1),
          n(n),
          nextId(n)            
    {
        iota(par.begin(), par.end(), 0);
        for (int i = 1; i <= n; ++i) {
            elemwhichnode[i] = i;        
            sum[i] = i;             
        }
    }
    int find(int v) {                     
        return (v == par[v] ? v : (par[v] = find(par[v])));
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    int get_size(int v) {
        return sz[find(v)];
    }
    int get_sum(int v) {
        return sum[find(v)];
    }
    int count() {
        return n; 
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return;
        n--;
        if (rank[v] > rank[u]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        sum[u] += sum[v];
        if (rank[u] == rank[v]) rank[u]++;
        // u is the parent;
    }

    void erase(int v) {
        int nv = elemwhichnode[v];
        if (nv == 0) return;            // already deleted
        int pv = find(nv);
        sz [pv] -= 1;
        sum[pv] -= v;
        elemwhichnode[v] = 0;               // mark deleted
    }
    /* move p -> set(q) */
    void move(int u, int v) {
        if(elemwhichnode[u] == 0) return;
        
        int pu = find(elemwhichnode[u]);
        int pv = find(elemwhichnode[v]);
        if (pu == pv) return;  

        erase(u);

        nextId++;
        par [nextId] = nextId;
        rank[nextId] = 0;
        sz  [nextId] = 1;
        sum [nextId] = u;

        elemwhichnode[u] = nextId;

        join(nextId, pv);
    }

    pair<int, ll> query(int p) {
        int r = find(elemwhichnode[p]);
        return { (int)sz[r], sum[r] };
    }
};
 
void solve() {
    int n, m;
    while(cin >> n >> m) {
        DSU obj(n, m);
        while(m--) {
            int ty; cin >> ty;
            if(ty < 3) {
                int p, q;
                cin >> p >> q;
                (ty == 1 ? obj.join(obj.elemwhichnode[p], obj.elemwhichnode[q]) : obj.move(p, q));
            }
            else {
                int p; cin >> p;
                auto [x, y] = obj.query(p);
                cout << x << " " << y << "\n";
            }
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
