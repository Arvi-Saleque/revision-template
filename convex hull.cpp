#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 9, mod = 998244353;
struct point{ 
    ll x, y;
    point() {
        x = -1;
        y = -1;
    }
    bool operator < (const point &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
    bool operator == (const point &p) const {
        return x == p.x && y == p.y;
    }
};
ll cross (point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<point> ConvexHull(vector<point>&p, int n) {
    int sz = 0;
    vector<point> hull(n + n);
    sort(p.begin(), p.end());
  for(int i = 0; i < n; ++i) {
        while (sz > 1 and cross(hull[sz - 2], hull[sz - 1], p[i]) < 0) --sz;
        hull[sz++] = p[i];
    }
    for(int i = n - 2, j = sz + 1; i >= 0; --i) {
        while (sz >= j and cross(hull[sz - 2], hull[sz - 1], p[i]) < 0) --sz;
        hull[sz++] = p[i];
    }
    hull.resize(sz - 1);
    return hull;
} 
void solve() {
    int n;
    cin >> n;
    vector<point> p(n);
    map<point, int> mp;
    for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        mp[p[i]] = i + 1;
    }
    auto idx = mp;

    auto convex = ConvexHull(p, n);

    for(int i = 0; i < convex.size(); i++) {
        mp.erase(convex[i]);
    }

    if(mp.empty()) {
        cout << "-1\n";
        return;
    }
    vector<point> nonconvex;
    for(auto [x, y] : mp) {
        nonconvex.push_back(x);
    }
    sort(nonconvex.begin(), nonconvex.end(), [&](point a, point b) -> bool {
        return (idx[a] < idx[b]);
    });

    auto cross = [](const point& a, const point& b, const point& c) -> ll {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    };

    auto area = [&](point p1, point p2, point p3) {
        auto [x1, y1] = p1;
        auto [x2, y2] = p2;
        auto [x3, y3] = p3;

        ll val = x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1;
        val = abs(val);
        return val;
    };

    auto check = [&](point a, point b, point c, point k) {
        ll are1 = area(a, b, k);
        ll are2 = area(b, c, k);
        ll are3 = area(a, c, k);
        ll are = area(a, b, c);
        ll tot = are1 + are2 + are3;
        return (tot == are);
    };

    auto dis = [&](point a, point b) {
        return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
    };

    vector<array<int, 4>> ans;

    int sz = convex.size();
    for(int i = 0; i < nonconvex.size(); i++) {
        point pi = nonconvex[i];

        point pj = convex[0];
        
        for(int j = 1; j < convex.size() - 1; j++) {
            point pk = convex[j];
            point pl = convex[j + 1];

            if(check(pj, pk, pl, pi)) {
                cout << idx[pi] << " " << idx[pj] << " " << idx[pk] << " " << idx[pl] << "\n";
                return;
            }
        }

    }
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
