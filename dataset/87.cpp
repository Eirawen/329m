class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> st;
        int n = target.size();
        int minInc = 0;
        for(int i = 0; i < n; i++) {
            if(!st.empty() && st.top() > target[i])
                minInc += st.top() - target[i];
            while(!st.empty() && st.top() > target[i])
                st.pop();
            st.push(target[i]);
        }
        minInc += st.top();
        return minInc;
    }
};