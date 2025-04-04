// https://codeforces.com/contest/2086/problem/E

// sometimes we can observe and reduct the value to very lower
// here k can be max 120 
// also there can be max 30*120 difference type of f(y-1,k) call occur
// so map dp wonts exceed too much 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 9;
vector<ll> v;
void pre() {
	ll cur = 1, d = 1;
	while(cur <= 1e18) {
		v.push_back(cur);
		d *= 4;
		cur += d;
	}
}

void solve() {
	ll l, r, k;
	cin >> l >> r >> k;
	if(k > 120) {
		cout << "0\n";
		return;
	}

	map<array<ll,2>, ll> dp;

	function<ll(ll, int)> f = [&](ll x, int k) -> ll {
		//cout << x << " " << k << "\n";
		if(dp.count({x, k})) return dp[{x, k}];
		if(k == 0) return 1LL;
		if(x == 0) return 0LL;
		ll ans = 0;
		auto it = upper_bound(v.begin(), v.end(), x);
		it--;
		ll val = *it;
		//cout << val << "\n";
		ans = f(val - 1, k) + f(x - val, k - 1);
		return dp[{x, k}] = ans;
	};

	//cout << f(1, 1) << "\n";

	cout << f(r, k) - f(l - 1, k) << "\n";
}

int main() {
	pre();
	ios_base::sync_with_stdio(0);
	int t = 1;
	cin >> t;
	while(t--) {
		solve();
	}
}
