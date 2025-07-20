// https://codeforces.com/contest/2126/problem/G1

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;

class SegTlazy {
public:
    struct node {
        int cursum, premn, premx;
        node *left, *right;
        node(int _cur = 0, int mn = 1e9, int mx = -1e9)
            : cursum(_cur), premn(mn), premx(mx), left(nullptr), right(nullptr) {}
    };
    vector<int> a;
    vector<node*> roots; // persistent versions
    int n;
    SegTlazy() {
        n = 0;
        a.clear();
        roots.clear();
    }
    void init(int _n) {
        n = _n;
        a.assign(n + 1, 1); // 1-based intitially all 1
        roots.clear();
    }
    void merge(node* nd, node* l, node* r) {
        nd->cursum = l->cursum + r->cursum;
        nd->premn = min(l->premn, l->cursum + r->premn);
        nd->premx = max(l->premx, l->cursum + r->premx);
    }
    node* build(int b, int e) {
        if (b == e) {
            return new node(a[b], a[b], a[b]);
        }
        int mid = (b + e) >> 1;
        node* cur = new node();
        cur->left = build(b, mid);
        cur->right = build(mid + 1, e);
        merge(cur, cur->left, cur->right);
        return cur;
    }
    node* update(node* prev, int b, int e, int pos, int val) {
        if (b == e) {
            return new node(val, val, val);
        }
        int mid = (b + e) >> 1;
        node* cur = new node();
        if (pos <= mid) {
            cur->left = update(prev->left, b, mid, pos, val);
            cur->right = prev->right;
        } else {
            cur->left = prev->left;
            cur->right = update(prev->right, mid + 1, e, pos, val);
        }
        merge(cur, cur->left, cur->right);
        return cur;
    }
    node query(node* nd, int b, int e, int i, int j) {
        if (!nd || j < b || e < i) {
            return node(0, 1e9, -1e9);
        }
        if (i <= b && e <= j) {
            return *nd;
        }
        int mid = (b + e) >> 1;
        node l = query(nd->left, b, mid, i, j);
        node r = query(nd->right, mid + 1, e, i, j);
        node res;
        merge(&res, &l, &r);
        return res;
    }
};
void solve() {
    int n; cin >> n;
    vector<int> v(n + 2);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        mx = max(mx, v[i]);
    }
    vector<vector<int>> pos(mx + 1);
    for(int i = 1; i <= n; i++) {
        pos[v[i]].push_back(i);
    }
    SegTlazy tree;
    tree.init(n + 1);
    tree.roots.push_back(tree.build(0, n + 1)); // root 0 all 1
    for(int val = 1; val <= mx; val++) { // mid = 2 means root[2] -> root[1]
        auto cur = tree.roots.back();
        for(auto x : pos[val]) {
            cur = tree.update(cur, 0, n + 1, x, -1);
        }
        tree.roots.push_back(cur);
    }
    v[0] = v[n + 1] = -1;
    stack<int> leftst, rightst;
    leftst.push(0);
    rightst.push(n + 1);
    vector<int> L(n + 2), R(n + 2);
    for(int i = 1; i <= n; i++) {
        while(not leftst.empty() && v[leftst.top()] >= v[i]) {
            leftst.pop();
        }
        L[i] = leftst.top();
        leftst.push(i);
    }
    for(int i = n; i >= 1; i--) {
        while(not rightst.empty() && v[rightst.top()] >= v[i]) {
            rightst.pop();
        }
        R[i] = rightst.top();
        rightst.push(i);
    }
    auto get = [&](int l, int r, int j) { // [l, r] smaller indexes
        //cout << l << " " << r << " " << j << "\n";
        int lo = v[j], hi = mx, mid, ans = -1;
        while(lo <= hi) {
            mid = lo + hi >> 1;
            int sum1, mn1, mx2;
            sum1 = tree.query(tree.roots[mid - 1], 0, n + 1, l, j - 1).cursum;
            mn1 = tree.query(tree.roots[mid - 1], 0, n + 1, l, j - 1).premn;
            mx2 = tree.query(tree.roots[mid - 1], 0, n + 1, j, r).premx;
            mx2 += sum1;
            if (mx2 - mn1 >= 0) {
                ans = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        //cout << ans << "\n";
        return ans;
    };
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int curmn = v[i];
        int l = L[i];
        int r = R[i] - 1; 
        int mxmed = get(l, r, i);
        ans = max(ans, mxmed - curmn);
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
