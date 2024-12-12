/*
1 2 3 2 1
1 1 1 1 1
0 0 1 1 1
3
*/

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        const int n = target.size();
        vector<int> ans(n, 0);
        vector<int> stk;
        
        for (int i = 0; i < n; ++i) {
            if (stk.empty()) {
                ans[i] = target[i];
                stk.push_back(target[i]);
                // std::cout << i << " " << ans[i] << std::endl;
                continue;
            }
            auto it = lower_bound(stk.begin(), stk.end(), target[i]);
            if (it == stk.begin()) {
                ans[i] = target[i];
                // std::cout << i << " " << ans[i] << std::endl;
            } else {
                --it;
                ans[i] = target[i] - *it;
                // std::cout << i << " " << ans[i] << std::endl;
            }
            while (!stk.empty() && stk.back() >= target[i])
                stk.pop_back();
            stk.push_back(target[i]);
        }

        stk.clear();
        for (int i = n-1; i >= 0; --i) {
            if (stk.empty()) {
                ans[i] = min(ans[i], target[i]);
                // std::cout << i << " " << ans[i] << std::endl;
                stk.push_back(target[i]);
                continue;
            }
            auto it = upper_bound(stk.begin(), stk.end(), target[i]);
            if (it == stk.begin()) {
                ans[i] = min(ans[i], target[i]);
                // std::cout << i << " " << ans[i] << std::endl;
            } else {
                --it;
                ans[i] = min(ans[i], target[i] - *it);
                // std::cout << i << " " << ans[i] << std::endl;
            }
            while (!stk.empty() && stk.back() >= target[i])
                stk.pop_back();
            stk.push_back(target[i]);
        }

        return accumulate(ans.begin(), ans.end(), 0);
    }
};

// 3 5 4  7 6 2