// https://codeforces.com/gym/102964/problem/F

// if I need to make any inc/dec sequence and 1-n all are present 
// then i can check only if 1 and n both present

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 300002, mod = 1e9 + 7;
int n, m; // n size m values
int dp[2002][2002][2][2];
int f(int pos, int cur, bool f1, bool fm) {
    if(cur < 1 || cur > m) return 0;
    //cout << pos << " " << cur << " " << f1 << " " << fm << "\n";
    if(n == pos) {
        f1 |= (cur == 1);
        fm |= (cur == m);
        if(f1 & fm) return 1;
        else return 0;
    }
    int &ans = dp[pos][cur][f1][fm];
    if(ans != -1) return ans;
    ans = 0;
    ans = (ans + f(pos + 1, cur + 1, (f1 | (cur == 1)), (fm | (cur == m)))) % mod;
    ans = (ans + f(pos + 1, cur - 1, (f1 | (cur == 1)), (fm | (cur == m)))) % mod;
    return ans;
}
void solve() {
    cin >> n >> m;
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans = (ans + f(1, i, (i == 1), (i == m))) % mod;
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}

// https://codeforces.com/contest/2086/problem/D

// if i need to work with even and odd indicices something like that
// we need evensum and odd sum
// we can reduce 1 state using prefix sum

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int const N = 5e5 + 2, mod = 998244353;
int f[N], invf[N];
ll power(ll a, ll b) {
	ll res = 1;
	bool flag = (a >= mod);
	while(b) {
		if(b & 1) {
			res *= a;
			if(res >= mod) {
				res %= mod;
				flag = 1;
			}
		}
		a *= a;
		if(a >= mod) {
			a %= mod;
			flag = 1;
		}
		b >>= 1;
	}
	return (res + (flag * mod)) % mod;
}
void pre() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = 1LL * i * f[i - 1] % mod;
    }
    invf[N - 1] = power(f[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--) {
        invf[i] = 1LL * invf[i + 1] * (i + 1) % mod;
    }
}
int nCr(int n, int r) {
    if(n < 0 || r < 0 || r > n) return 0;
    if(n == 0 && r == 0) return 1;
    return 1LL * f[n] * invf[r] % mod * invf[n - r] % mod;
}

void solve() {
	vector<int> c(27, 0);
	vector<int> pre(27, 0);
	int tot = 0;
	for(int i = 1; i <= 26; i++) {
		cin >> c[i];
		pre[i] = pre[i - 1] + c[i];
		tot += c[i];
	}
	int v1 = (tot + 1) / 2;
	int v2 = tot - v1;
	for(int i = 1; i <= 26; i++) {
		if(c[i] > v1) {
			cout << 0 << "\n";
			return;
		}
	}

	/*
	map<array<int, 3>, ll> mp;

	function<int(int, int, int)> f = [&](int pos, int evsum, int oddsum) -> int {
		if(pos > 26) return 1;
		if(mp.count({pos, evsum, oddsum})) return mp[{pos, evsum, oddsum}];
		ll &ans = mp[{pos, evsum, oddsum}];
		ans = f(pos + 1, evsum, oddsum) % mod;
		if(c[pos] == 0) return ans;
		ans = 0;
		int remodd = v1 - oddsum;
		int remev = v2 - evsum;
		ans = (ans + (1LL * nCr(remodd, c[pos]) * f(pos + 1, evsum, oddsum + c[pos])) % mod) % mod;
		ans = (ans + (1LL * nCr(remev, c[pos]) * f(pos + 1, evsum + c[pos], oddsum)) % mod) % mod;
		return ans;
	};
	*/

	vector<vector<ll>> dp(27, vector<ll>(v1 + 2, -1));
	function<int(int, int)> rec = [&](int pos, int oddsum) -> ll {
		if(pos > 26 || oddsum > v1) return 1LL;
		ll &ans = dp[pos][oddsum];
		if(ans != -1) return ans % mod;
		ans = rec(pos + 1, oddsum) % mod;
		if(c[pos] == 0) return ans;
		ans = 0;
		int remodd = v1 - oddsum;
		int remev = v2 - (pre[pos - 1] - oddsum);
		ans = (ans + (1LL * nCr(remodd, c[pos]) * rec(pos + 1, oddsum + c[pos])) % mod) % mod;
		ans = (ans + (1LL * nCr(remev, c[pos]) * rec(pos + 1, oddsum)) % mod) % mod;
		return ans;
	};

	cout << rec(1, 0) << "\n";

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
