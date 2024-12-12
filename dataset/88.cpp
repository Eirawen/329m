class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        std::vector<int> increasing_st;
        int ans = 1;

        for (int i = 0; i < target.size(); i++) {
            while (!increasing_st.empty() && target[increasing_st.back()] > target[i]) {
                int prev_index = increasing_st.back();
                int prev_val = prev_index == 0
                    ? 1
                    : target[prev_index - 1];

                if (target[prev_index] > prev_val) {
                    ans += (target[prev_index] - prev_val);
                }

                increasing_st.pop_back();
            }

            increasing_st.push_back(i);
        }

        while (!increasing_st.empty()) {
            int prev_index = increasing_st.back();
            int prev_val = prev_index == 0
                ? 1
                : target[prev_index - 1];

            if (target[prev_index] > prev_val) {
                ans += (target[prev_index] - prev_val);
            }

            increasing_st.pop_back();
        }

        return ans;
    }
};