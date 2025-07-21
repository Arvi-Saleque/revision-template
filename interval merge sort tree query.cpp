#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;

class SegTlazy {
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node {
        vector<pair<int, int>> vec;
        node() {
            vec.clear();
        }
        node(vector<pair<int, int>> v) {
            vec.swap(v);
            int mn = 1e9;
            for(auto &p: vec){
                mn = min(mn, p.second);
                p.second = mn;
            }
        }
    };  
    vector<int> a;
    vector<node> t;
    int n; 
    SegTlazy() {
        n = 0;
        a.clear();
        t.clear();
    }
    void init(int n, int val = 1) {
        this -> n = n;
        a.resize(n + 1, val);
        t.resize(4*n + 1, node());
    }
    void merge(node &ND, node &L, node &R) {
        if(L.vec.empty()) {
            ND = R;
            return;
        }
        if(R.vec.empty()) {
            ND = L;
            return;
        }
        ND.vec.clear();
        int l = 0, r = 0, mn = 1e9;
        while(l<L.vec.size() || r<R.vec.size()){
            pair<int,int> cur;
            if(r==R.vec.size() || (l<L.vec.size() && L.vec[l].first<=R.vec[r].first))
                cur = L.vec[l++];
            else cur = R.vec[r++];
            mn = min(mn, cur.second);
            ND.vec.push_back({cur.first, mn});                           
        }
    }
    void build(int nd, int b, int e) {
        if(b == e) {
            t[nd].vec.push_back({b + a[b] - 1, a[b]});
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
     int query(int nd,int b,int e,int i,int j,int r){         
        if(j<b||e<i) return INT_MAX;
        if(i<=b&&e<=j){
            const auto &v = t[nd].vec;
            if(v.empty() || v.front().first>r) return 1e9;
            int cnt = upper_bound(v.begin(),v.end(),r, [](int val,const pair<int,int>&p){ 
                return val < p.first; 
            }) - v.begin();
            return v[cnt-1].second;                   
        }
        int mid=(b+e)>>1;
        return min(query(lc,b,mid,i,j,r), query(rc,mid+1,e,i,j,r));                 
    }
};


class segtree {
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node {
        bitset<26> bit;
        node() {
            bit.reset();
        };
        node(bitset<26> b) : bit(b) {}
    }; 
    vector<char> a;
    vector<node> t;
    int n; 
    segtree(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void merge(node &ND, node L, node R) {
        ND.bit = L.bit | R.bit;
    }
    void build(int nd, int b, int e) {
        if(b == e) {
            bitset<26> bit;
            bit[a[b] - 'a'] = 1;
            t[nd] = node(bit);
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd, int b, int e, int i, int j) {
        if(j < b || e < i) return node();
        if(i <= b && e <= j) {
            return t[nd];
        }
        int mid = b + e >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid + 1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
};

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    s = '.' + s;

    segtree treedis(n);
    for(int i = 1; i <= n; i++) {
        treedis.a[i] = s[i];
    }
    treedis.build(1, 1, n);

    SegTlazy tree[27];
    tree[1].init(n, 1);
    tree[1].build(1, 1, n);
    for(int d = 2; d <= 26; d++) {
        tree[d].init(n, n + 1);
        int l = 1, r = 1;
        map<char, int> mp;
        while(r <= n) {
            mp[s[r]]++;
            if(mp.size() == d) {
                while(mp.size() == d && l < r) {
                    tree[d].a[l] = (r - l + 1);
                    mp[s[l]]--;
                    if(mp[s[l]] == 0) {
                        mp.erase(s[l]);
                    }
                    l++;
                }
            }
            r++;
        }
        tree[d].build(1, 1, n);
    }

    int q; cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        int distinct = treedis.query(1, 1, n, l, r).bit.count();
        cout << tree[distinct].query(1, 1, n, l, r, r) << "\n";
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
