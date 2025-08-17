#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e4 + 1, mod = 998244353;
// must filled what leafs hold
// make sure node() what return when out of bounds
class SegTlazy {
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node {
        int g, l;
        node(int _g = 0, int _l = 1) : g(_g), l(_l) {}
    }; 
    vector<int> a;
    vector<node> t;
    int n; 
    SegTlazy(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void merge(node &ND, node L, node R) {
        ND.g = gcd(L.g, R.g);
        ND.l = min(N, lcm(L.l, R.l));
    }
    void upd(int nd, int b, int e, int i) {
        if(i < b || e < i) return;
        if(i == b && b == e) {
            t[nd].g = 0;
            t[nd].l = 1;
            return;
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, i);
        upd(rc, mid + 1, e, i);
        merge(t[nd], t[lc], t[rc]);
    }
    void build(int nd, int b, int e) {
        if(b == e) {
            t[nd].g = a[b];
            t[nd].l = a[b];
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd, int b, int e, int i, int j) {
        if(j < b || e < i) return node();          
        if(i <= b && e <= j) return t[nd];
        int mid = (b + e) >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid + 1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
    int findleftlcm(int nd, int b, int e, int acc, int x) {
        if(b == e) {
            int val = min(N, lcm(acc, t[nd].l));
            if(val >= x) return b;
            return -1;
        }
        int mid = b + e >> 1;
        int val = min(N, lcm(acc, t[lc].l));
        if(val >= x) {
            return findleftlcm(lc, b, mid, acc, x);
        }
        else {
            return findleftlcm(rc, mid + 1, e, val, x);
        }
    }
    int findrightlcm(int nd, int b, int e, int acc, int x) { // return strictly greater than pos
        if(b == e) {
            int val = min(N, lcm(acc, t[nd].l));
            if(val > x) return b;
            return -1;
        }
        int mid = b + e >> 1;
        int val = min(N, lcm(acc, t[lc].l));
        if(val > x) {
            return findrightlcm(lc, b, mid, acc, x);
        }
        else {
            return findrightlcm(rc, mid + 1, e, val, x);
        }
    }
    int findleftgcd(int nd, int b, int e, int acc, int x) {
        if(b == e) {
            int val = gcd(acc, t[nd].g);
            if(val != 0 && val <= x) return b;
            return -1;
        }
        int mid = b + e >> 1;
        int val = gcd(acc, t[lc].g);
        if(val != 0 && val <= x) {
            return findleftgcd(lc, b, mid, acc, x);
        }
        else {
            return findleftgcd(rc, mid + 1, e, val, x);
        }
    }
    int findrightgcd(int nd, int b, int e, int acc, int x) { // return strictly greater than pos
        if(b == e) {
            int val = gcd(acc, t[nd].g);
            if(val != 0  && val < x) return b;
            return -1;
        }
        int mid = b + e >> 1;
        int val = gcd(acc, t[lc].g);
        if(val != 0  && val < x) {
            return findrightgcd(lc, b, mid, acc, x);
        }
        else {
            return findrightgcd(rc, mid + 1, e, val, x);
        }
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n + 1);
    SegTlazy tree(n);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        tree.a[i] = v[i];
    }
    tree.build(1, 1, n);
    ll ans = 0;     
    auto add = [&](int i, int g) {
        int l = g * k;
        if(l > N) return;
        int Lg = tree.findleftgcd(1, 1, n, 0, g);
        if(Lg == -1) return;
        if (tree.query(1, 1, n, 1, Lg).g != g) return;
        int Rg = tree.findrightgcd(1, 1, n, 0, g);
        if(Rg == -1) Rg = n + 1;
        Rg--;
        int Lc = tree.findleftlcm(1, 1, n, 1, l);
        if(Lc == -1) return;
        if (tree.query(1, 1, n, 1, Lc).l != l) return;
        int Rc = tree.findrightlcm(1, 1, n, 1, l);
        if(Rc == -1) Rc = n + 1;
        Rc--;
        ans += max(0, (min(Rg, Rc) - max(Lg, Lc) + 1)); 
    };
    for(int i = 1; i <= n; i++) {
        for(int j = 1; (1LL * j * j) <= v[i]; j++) {
            if(v[i] % j == 0) {
                int d = (v[i] / j);
                add(i, j);
                if(j != d) {
                    add(i, d);
                }
            }
        }
        tree.upd(1, 1, n, i);
    }
    cout << ans << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1, cs = 1;
    cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
