// https://codeforces.com/problemset/problem/1554/D

// when someething realtead to construrct with character
// at first try if it possible with 1 char then  2 char
// if possible but need to merge then check some how you can merge
// here you can use 1 extra char to merge both side

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 1e5 + 9, mod = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "a\n";
        return;
    }
    int l, r;
    string ans;
    if(n % 2 == 0) {
        l = n / 2;
        r = l - 1;
        for(int i = 1; i <= l; i++) ans.push_back('a');
        ans.push_back('b');
        for(int i = 1; i <= r; i++) ans.push_back('a');
    }
    else {
        l = n / 2;
        r = l - 1;
        for(int i = 1; i <= l; i++) ans.push_back('a');
        ans.push_back('b');
        ans.push_back('c');
        for(int i = 1; i <= r; i++) ans.push_back('a');
    }
    // /cout << ans.size() << "\n";
    cout << ans << "\n" ;
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

// https://www.codechef.com/problems/DIANE

// focus on small constraint and check if it possible with only 
// 2/3 value and try to merge others 

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 300002, M = 1e5 - 2, mod = 1e9 + 7;
void solve() {
    int d; cin >> d;
    if(d == 0) {
        cout << 1 << "\n" << 1 << "\n";
        return;
    }
    vector<int> ans;
    while(d > M) {
        int a = 1;
        while((1LL * a * a * a) <= d) {
            a++;
        }
        a--;
        for(int i = 1; i <= a; i++) {
            ans.push_back(a + 1);
        }
        for(int i = 1; i <= a; i++) {
            ans.push_back(a + 2);
        }
        d -= (1LL * a * a * a);
        if(d > M) {
            ans.push_back(1);
        }
    }
    if(d > 0) {
        ans.push_back(1);
        ans.push_back(d + 1);
        ans.push_back(d + 2);
    }
    cout << ans.size() << "\n";
    for(auto x : ans) {
        cout << x << " ";
    }
    cout << "\n";
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
