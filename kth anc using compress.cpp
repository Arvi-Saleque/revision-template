// https://www.hackerrank.com/challenges/kth-ancestor/problem

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 1e6 + 2, mod = 1e9 + 7;
void solve() {
  int n;
  cin >> n;
  vector<int> nodes;
  vector<array<int, 2>> e;
  for(int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    nodes.push_back(u);
    if(v > 0) nodes.push_back(v);
    e.push_back({u, v});
  }
  vector<array<int, 3>> Q;
  int q; cin >> q;
  while(q--) {
    int ty; cin >> ty;
    if(ty == 1) {
      int x; cin >> x;
      Q.push_back({ty, x, 0});
      nodes.push_back(x);
    }
    else {
      int x, y;
      cin >> x >> y;
      Q.push_back({ty, x, y});
      nodes.push_back(x);
      if(ty == 0) nodes.push_back(y);
    }
  }

  sort(nodes.begin(), nodes.end());
  nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

  auto get = [&](int x) {
    return (lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin()) + 1;
  };

  for(auto &[x, y] : e) {
    x = get(x);
    if(y > 0) y = get(y);
    n = max(n, x);
    n = max(n, y);
  }

  for(auto &[ty, x, y] : Q) {
    if(ty == 0) {
      x = get(x);
      y = get(y);
      n = max(n, x);
      n = max(n, y);
    }
    else if(ty == 1) {
      x = get(x);
      n = max(n, x);
    }
    else {
      x = get(x);
      n = max(n, x);
    }
  }

  vector<bool> present(n + 1, 0);
  vector<vector<int>> g(n + 1);
  int root = 0;
  for(auto [x, y] : e) {
    if(y == 0) {
      root = x;
    }
    else {
      g[x].push_back(y);
      g[y].push_back(x);
    }
    present[x] = 1;
    if(y > 0) present[y] = 1;
  }

  int height = __lg(n) + 1;
  vector<vector<int>> par(n + 1, vector<int>(height + 1));

  function<void(int, int)> dfs = [&](int u, int p) -> void {
    par[u][0] = p;
    for(int j = 1; j <= height; j++) {
      par[u][j] = par[par[u][j - 1]][j - 1];
    }
    for(auto v : g[u]) if(v != p) {
      dfs(v, u);
    }
  };

  dfs(root, 0);

  auto print = [&](int u, int k) {
    while(k > 0) {
      int pos = 31 - __builtin_clz(k); // log2(k) or heighest set bit in k
      if(pos > height) return 0;
      u = par[u][pos];
      k -= (1 << pos);
    }
    return u;
  };

  for(auto [ty, x, y] : Q) {
    if(ty == 0) {
      par[y][0] = x;
      present[y] = 1;
      for(int j = 1; j <= height; j++) {
        par[y][j] = par[par[y][j - 1]][j - 1];
      }
    }
    else if(ty == 1) {
      present[x] = 0;
    }
    else {
      int k = y;
      if(!present[x]) {
        cout << 0 << "\n";
      }
      else {
        int nd = print(x, k);
        cout << ((nd == 0 || !present[nd]) ? 0 : nodes[nd - 1]) << "\n";
      }
    }
  }

}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
