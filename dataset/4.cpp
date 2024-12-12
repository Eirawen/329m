class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> left(n);
        multiset<int> st;
        for(int i=0;i<n;i++){
            if(st.size()==0)left[i]=0;
            else{
                left[i]=*st.rbegin();
            }
            st.insert(height[i]);
        }
        vector<int> right(n);
        st.clear();
        for(int i=n-1;i>=0;i--){
            if(st.size()==0){
                right[i]=0;
            }else{
                right[i]=*st.rbegin();
            }
            st.insert(height[i]);
        }
        int ans=0;
        for(int i=1;i<n-1;i++){
            if(left[i]>height[i]&&right[i]>height[i])ans+=(min(left[i],right[i])-height[i]);
        }
        return ans;
    }
};