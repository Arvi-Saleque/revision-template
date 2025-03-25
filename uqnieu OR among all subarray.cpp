#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
class basicSegT 
{
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node
    {
        ll val;
        node() {
            val = 0;
        }
        node(ll v) {
            val = v;
        }
    };
    vector<int> a;
    vector<node> t;
    int n;
    basicSegT() {
        a.clear();
        t.clear();
        n = 0;
    }   
    basicSegT(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void merge(node &ND, node L, node R) {
        ND.val = L.val | R.val;
    } 
    void build(int nd,int b,int e) {
        if(b == e) {
            t[nd] = a[b];
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid+1, e);
        merge(t[nd], t[lc], t[rc]);
    } 
    node query(int nd,int b,int e,int i,int j) {
        if(j < b || e < i) return 0;
        if(i <= b && e <= j) return t[nd];
        int mid = (b+e) >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid+1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
};
void solve() {
    int n; cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    basicSegT tree(n + 1);
    for(int i = 1; i <= n; i++) {
        tree.a[i] = v[i];
    }
    tree.build(1, 1, n);

    vector<vector<int>> bitv(30);
    for(int i = 0; i < 30; i++) {
        for(int j = 1; j <= n; j++) {
            if(v[j] & (1 << i)) {
                bitv[i].push_back(j);
            }
        }
    }

    int ans = 0;
    map<int, bool> has;
    for(int i = 1; i <= n; i++) {
        int cur = 0, next = i, cnt = 0;
        while(next <= n) {
            cur |= tree.query(1, 1, n, i, next).val;
            if(!has.count(cur)) cnt++;
            has[cur] = 1;
            int mn = n + 2;
            for(int j = 0; j < 30; j++) {
                if(!(cur & (1 << j))) {
                    if(bitv[j].size() > 0) {
                        auto it = lower_bound(bitv[j].begin(), bitv[j].end(), i);
                        if(it != bitv[j].end()) {
                            mn = min(mn, *it);
                        }
                    }
                }
            }
            next = mn;
        }
        //cout << i << " " << cnt << "\n";
        ans += cnt;
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
