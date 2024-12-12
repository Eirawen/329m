class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int>st;
        int ans = 0;
        for(auto it : target){
            int mx= 0;
            while(!st.empty() && st.top()>it){
                mx = max(mx, st.top());
                st.pop();
            }
            ans += max(mx,it) - it;
            st.push(it);
        }
        if(!st.empty()) ans += st.top();
        return ans;
    }
};