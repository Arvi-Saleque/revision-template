// https://leetcode.com/problems/beautiful-array/

// if need to construct any array first try if it is possible
// to divide the array into left and right part
// then try to divided each part and solve recursavley 


class Solution {
public:
    map<int, vector<int>> mp;
    vector<int> beautifulArray(int n) {
        if(n == 1) return {1};
        if(mp.count(n)) return mp[n];
        auto l = beautifulArray((n + 1) / 2);
        auto r = beautifulArray(n / 2);
        vector<int> ans;
        for(auto x : l) {
            ans.push_back(2 * x - 1);
        }
        for(auto x : r) {
            ans.push_back(2 * x);
        }
        return mp[n] = ans;
    }
};
