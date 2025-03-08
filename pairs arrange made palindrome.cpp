// odd <= 1
// so Xor = 0 means odd = 0
// Xor = 1 means odd = 1 for this
// i need to fllip exactly one bit of a-z

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e5 + 9, mod = 998244353;
void solve() {
    string s;
    cin >> s;
    map<int, ll> freq;
    int mask = 0;
    // before processing any characters, we have one occurrence of mask 0
    freq[mask] = 1;
    ll result = 0;
    // iterate over each character in the string
    for (char c : s) {
        // Toggle the bit corresponding to the current character
        mask ^= (1 << (c - 'a'));
        // count substrings ending here that are already balanced (exact match)
        result += freq[mask];
        // count substrings ending here that differ by exactly one bit
        for (int b = 0; b < 26; ++b) {
            result += freq[mask ^ (1 << b)];
        }
        // update frequency for the current mask
        freq[mask]++;
    }
    cout << result << "\n";
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