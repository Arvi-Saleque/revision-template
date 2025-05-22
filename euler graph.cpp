#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int M = 2e5 + 9, mod = 1e9 + 7;
const ll inf = 1e18;

/*
all the edges should be in the same connected component
#undirected graph: euler path: all degrees are even or exactly two of them are odd.
#undirected graph: euler circuit: all degrees are even
#directed graph: euler path: for all -> indeg = outdeg or 
in - out == 1 && out - in == 1
#directed graph: euler circuit: for all -> indeg = outdeg
*/

struct EulerGraph {
    vector<vector<pair<int, int>>> g;
    vector<int> done, path, edges, indeg, outdeg;
    vector<bool> visedge;
    bool isdirected;
    int n, m;
    EulerGraph(int n, int m, bool isd = 1) : n(n), m(m) {
        g.resize(n + 1);
        done.assign(n + 1, 0);
        indeg.assign(n + 1, 0);
        outdeg.assign(n + 1, 0);
        visedge.assign(m + 1, 0);
        isdirected = isd;
        take_input();
    }
    void take_input() {
        for(int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            u++, v++;
            g[u].push_back({v, i});
            indeg[v]++, outdeg[u]++;
            if(!isdirected) {
                g[v].push_back({u, i});
                indeg[u]++;
                outdeg[v]++;
            }
        }
    }
    void dfs(int u) {
        while(done[u] < g[u].size()) {
            auto [v, eid] = g[u][done[u]++];
            if(!isdirected) {
                if(visedge[eid]) continue;
                visedge[eid] = 1;
            }
            dfs(v);
            edges.push_back(eid);
        }
        path.push_back(u);
    }
    pair<int, bool> find_start() { // true means any otherwise fixed
        if(isdirected) {
            bool allsame = 1;
            for(int i = 1; i <= n; i++) {
                if(indeg[i] != outdeg[i]) {
                    allsame = 0;
                    break;
                }
            }
            if(allsame) return {-1, 1}; // any can be root

            int incnt = 0, outcnt = 0, node = -1; // must be 1 1 and remaining same
            for(int i = 1; i <= n; i++) {
                if((outdeg[i] - indeg[i]) > 1 or (indeg[i] - outdeg[i]) > 1) {
                    return {-1, 0};
                } 
                if((outdeg[i] - indeg[i]) == 1) {
                    node = i;
                    outcnt++;
                }
                if((outdeg[i] - indeg[i]) == -1) incnt++;
            }
            if((incnt == 1 && outcnt == 1)) return {node, 1};
            return {-1, 0};
        }
        else {
            bool alleven = 1;
            for(int i = 1; i <= n; i++) {
                if(indeg[i] & 1) {
                    alleven = 0;
                    break;
                }
            }
            if(alleven) return {-1, 1}; // any can be root

            int odd = 0, node = -1;
            for(int i = 1; i <= n; i++) {
                if(indeg[i] & 1) {
                    odd++;
                    node = i;
                }
            }
            if(odd == 2) return {node, 1};
            return {-1, 0};
        }
    }
    void solve() {  
        auto [root, flag] = find_start();
        if(isdirected) {
            if(!flag) {
                cout << "No\n";
                return;
            } 
            else {
                if(m == 0) {
                    cout << "Yes\n";
                    cout << 0 << "\n\n";
                    return;
                }
                if(root == -1) {
                    for(int i = 1; i <= n; i++) {
                        if(outdeg[i] > 0) {
                            root  = i;
                            break;
                        }
                    }
                }
                dfs(root);
                reverse(path.begin(), path.end());
                reverse(edges.begin(), edges.end());
                if(path.size() != m + 1) {
                    cout << "No\n";
                    return;
                }
                cout << "Yes\n";
                // print vertices
                for (int i = 0; i < (int)path.size(); i++) {
                    cout << path[i] - 1;
                    if (i + 1 < (int)path.size()) cout << ' ';
                }
                cout << '\n';

                // print edges
                for (int i = 0; i < (int)edges.size(); i++) {
                    cout << edges[i] - 1;
                    if (i + 1 < (int)edges.size()) cout << ' ';
                }
                cout << '\n';
            }
        }
        else {
            if(!flag) {
                cout << "No\n";
                return;
            } 
            else {
                if(m == 0) {
                    cout << "Yes\n";
                    cout << 0 << "\n\n";
                    return;
                }
                if(root == -1) {
                    for(int i = 1; i <= n; i++) {
                        if(indeg[i] > 0) {
                            root  = i;
                            break;
                        }
                    }
                }
                dfs(root);
                reverse(path.begin(), path.end());
                reverse(edges.begin(), edges.end());
                if(path.size() != m + 1) {
                    cout << "No\n";
                    return;
                }
                cout << "Yes\n";
                // print vertices
                for (int i = 0; i < (int)path.size(); i++) {
                    cout << path[i] - 1;
                    if (i + 1 < (int)path.size()) cout << ' ';
                }
                cout << '\n';

                // print edges
                for (int i = 0; i < (int)edges.size(); i++) {
                    cout << edges[i] - 1;
                    if (i + 1 < (int)edges.size()) cout << ' ';
                }
                cout << '\n';
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    EulerGraph graph(n, m, 0);
    graph.solve();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
