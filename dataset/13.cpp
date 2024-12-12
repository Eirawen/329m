class Solution {
public:
    int trap(std::vector<int>& height) {
        std::unordered_map<int, int> highest_from_right;
        std::unordered_map<int, int> highest_from_left;
        std::stack<int> st;

        for (int i = 0; i < height.size(); ++i) {
            if (st.empty()) {
                st.push(i);
            } else {
                highest_from_left[i] = st.top();
                if (height[st.top()] < height[i])
                    st.push(i);
            }
        }

        while (!st.empty()) {
            st.pop();
        }

        for (int i = height.size() - 1; i >= 0; --i) {
            if (st.empty()) {
                st.push(i);
            } else {
                highest_from_right[i] = st.top();
                if (height[st.top()] < height[i])
                    st.push(i);
            }
        }

        int answ = 0;
        for (int i = 1; i < height.size() - 1; ++i) {
            if (std::min(height[highest_from_right[i]], height[highest_from_left[i]]) > height[i]) {
                answ += std::min(height[highest_from_right[i]], height[highest_from_left[i]]) - height[i];
            }
        }
        return answ;
    }
};