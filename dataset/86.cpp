class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        std::stack<int> s;
        const int n = target.size();
        s.emplace(target[0]);

        int ans = 0;
        for (int idx = 1; idx < n; idx++) {
            auto val = target[idx];     // 5
            int old_val;

            if (!s.empty() && s.top() > val) {
                old_val = s.top();
                ans += old_val - val;

                while (!s.empty() && s.top() > val) {
                    s.pop();
                }
            }

            if (s.empty() || s.top() < val) {
                // push!
                s.emplace(val);
            }
        }

        if (!s.empty())
            ans += s.top();
        
        
        return ans;
    }
};