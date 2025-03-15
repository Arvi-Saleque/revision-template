// https://www.spoj.com/problems/DSUBSEQ/en/

// for counting distinct subsequence 
// go from a to next a
// for example from a to next b,c,d,....z
// here main thing is you cant do take or not take

// another appraoch is 
// dp[i] represent number of distincs subsequence with first i char
// where last[ch] is the index of last occur of ch


void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<vector<int>> next(n, vector<int>(26, - 1));
    vector<int> cur(26, -1);
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 26; j++) {
            if(cur[j] == -1 || cur[j] == i) continue;
            next[i][j] = cur[j];
        }
        cur[s[i] - 'A'] = i;
    }

    vector<int> dp(n, -1);

    function<int(int)> f = [&](int pos) {
        int &ans = dp[pos];
        if(ans != -1) return ans;
        ans = 0;
        if(pos == n - 1) return ans = 1;
        for(int j = 0; j < 26; j++) {
            if(next[pos][j] == -1) continue;
            ans = (ans + f(next[pos][j])) % mod;;
        }
        int res = (1 + ans) % mod;
        return ans = res;
    };

    int ans = 0;
    for(int i = 0; i < 26; i++) {
        if(cur[i] == -1) continue;
        ans = (ans + f(cur[i])) % mod;
    }
    cout << (ans + 1) % mod << "\n";
}  

void solve() {
    string s; cin >> s;
    int n = s.size();
    s = '.' + s;
    vector<int> dp(n + 1, 0);
    vector<int> last(26, -1);
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        dp[i + 1] = (2LL * dp[i]) % mod;
        if(last[s[i + 1] - 'A'] != -1) {
            dp[i + 1] = (dp[i + 1] - dp[last[s[i + 1] - 'A'] - 1] + mod) % mod;
        } 
        last[s[i + 1] - 'A'] = i + 1;
    }
    cout << dp[n] << "\n";
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
