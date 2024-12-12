class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> st;
        st.push(target[0]);
        int ans = 0;
        int t;

        for(int i = 1 ; i < target.size();i++)
        {
            if(st.empty() || st.top() < target[i])
            {
                st.push(target[i]);
            }
            else if (target[i] < st.top())
            {
                while(!st.empty() && st.top() > target[i])
                {
                    t = st.top();
                    st.pop();
                    if(!st.empty())
                    {
                        ans += t - max(st.top(),target[i]);
                    }
                    else 
                    ans+=t - target[i];
                }
                if(st.empty() || target[i] > st.top())
                {
                    st.push(target[i]);
                }

            }
            
        }
        if(!st.empty())
            {
                ans+=st.top();
            }
            return ans;
        
    }
};