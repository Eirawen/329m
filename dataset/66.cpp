class Solution {
public:

    int minNumberOperations(vector<int>& target) {
        stack<int> st;
        vector<int> current(target.size(), 0);
        for (int i = 0; i < target.size(); ++i) {
            const auto& x = target[i];
            while (!st.empty() && st.top() >= x) {
                st.pop();
            }
            if (!st.empty()) {
                current[i] = st.top();
            }
            st.push(x);
        }
        while (!st.empty()) {
            st.pop();
        }

        int result = 0;
        for (int i = target.size() - 1; i >= 0; --i) {
            const auto& x = target[i];
            while (!st.empty() && st.top() > x) {
                st.pop();
            }
            if (!st.empty()) {
                current[i] = max(st.top(), current[i]);
            }
            st.push(x);
            
            result += x - current[i];
        }

        return result;
    }
};