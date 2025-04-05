// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3368
/*
when we need to find hoy mane array of a something like 
min(a1, a2, a3.........ak) = t
it is hard so we can just find how many there are >= t
then just solve(t) - solve(t - 1)
*/

#include<bits/stdc++.h>
using namespace std;

const int mod = 100000007; // 10^8 + 7

// given e[0], e[1], .... and t, find the
// number of sequences f[0], f[1], .... such that
// min(e[0] / f[0], e[1] / f[1], ....) >= t (floor division)
int solve_greater_than_or_equal(vector<int> e, int t) {
  int ans = 1;
  for (int i = 0; i < e.size(); i++) {
    ans = 1LL * ans * (e[i] / t + 1) % mod;
  }
  return ans;
}

// given e[0], e[1], .... and t, find the
// number of sequences f[0], f[1], .... such that
// min(e[0] / f[0], e[1] / f[1], ....) = t (floor division)
int solve_equal(vector<int> e, int t) {
  return (solve_greater_than_or_equal(e, t) - solve_greater_than_or_equal(e, t + 1) + mod) % mod;
}


int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m, t, cs = 0;
  while (cin >> n >> m >> t and n > 0) {
    vector<int> e;
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        int cnt = 0;
        while (n % i == 0) {
          ++cnt;
          n /= i;
        }
        e.push_back(cnt * m);
      }
    }
    if (n > 1) {
      e.push_back(1 * m);
    }
    cout << "Case " << ++cs << ": " << solve_equal(e, t) << '\n';
  }
  return 0;
}
