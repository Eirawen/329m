class Solution {
public:
    int trap(vector<int>& height) {
        unordered_map<int,int> m1,m2;
        stack<int> st;
        int n=height.size();
        for(int i=0;i<n;i++)
        {
            // while(st.size() && st.top()<=height[i])
            // st.pop();
            if(st.size())
            m1[i]=st.top();
            else
            m1[i]=-1;
            if(st.size()==0||st.top()<height[i])
            st.push(height[i]);
        }
        while(st.size())
        st.pop();
        for(int i=n-1;i>=0;i--)
        {
            // while(st.size() && st.top()<=height[i])
            // st.pop();
            if(st.size())
            m2[i]=st.top();
            else
            m2[i]=-1;
            if(st.size()==0||st.top()<height[i])
            st.push(height[i]);
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            if(m1[i]!=-1 && m2[i]!=-1 && height[i]<min(m2[i],m1[i]))
            {ans+=min(m2[i],m1[i])-height[i];}

        }
        return ans;

    }
};