class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        vector<pair<int, int>> st;
        int n = target.size();
        int64_t ans = 0;
        for (int i = 0; i < n; ++i) {
            if (st.empty()) {
                ans += target[i];
                st.push_back({target[i], target[i]});
            } else {
                if (target[i] >= st.back().second) {
                    ans += target[i] - st.back().second;
                    st.push_back({target[i], max(target[i], st.back().second)});
                } else {
                    int mx = 0;
                    while (!st.empty() && target[i] < st.back().second) {
                        mx = max(mx, st.back().second);
                        st.pop_back();
                    }
                    st.push_back({target[i], target[i]});
                    ans += mx < target[i] ? target[i] - mx : 0;                    
                }
            }
        }
        return ans;
    }
};