// For each of the contiguous subarrays of size K of each array, 
//you have to print the maximum integer.

#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    deque<int> dq;
    for(int i = 1; i <= n; i++) {
        while(!dq.empty() && v[dq.back()] < v[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if(dq.front() <= i - k) {
            dq.pop_front();
        }
        if(i >= k) {
            cout << v[dq.front()] << " ";
        }
    }
    cout << "\n";
}   
int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t; 
    while(t--) {
        // /cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}
