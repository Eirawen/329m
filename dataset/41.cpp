class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();        
        vector<int>nge(n,0);
        vector<int>pge(n,0);
        stack<int> st;
        int cap=0;
        
        for(int i=n-1;i>=0;i--){
            while(!st.empty() && st.top()<height[i]) st.pop();
            if(st.empty()) nge[i]=-1;
            else nge[i]=st.top(); 

            if(st.empty() || height[i]>st.top()) st.push(height[i]);
        }
        while(!st.empty()) st.pop();

        for(int i=0;i<n;i++){
            while(!st.empty() && st.top()<height[i]) st.pop();
            if(st.empty()) pge[i]=-1;
            else pge[i]=st.top(); 

            if(st.empty() || height[i]>st.top()) st.push(height[i]);
        }

        for(int i=0;i<n;i++){
            if(min(nge[i],pge[i])!=-1){
                cap+= (min(nge[i],pge[i])-height[i]);
            }
        }
        return cap;
        
        
    }
};