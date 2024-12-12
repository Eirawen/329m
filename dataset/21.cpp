class Solution {
public:
    int trap(vector<int>& h) {
        int n=h.size();
        map<int,int> nxt;
        stack<int> st;
        for(int i=n-1;i>=0;i--){
            while(!st.empty()){
                if(h[st.top()]<=h[i]){
                    st.pop();
                }
                else break;
            }
            if(st.empty()){
                nxt[i]=0;
            }
            else nxt[i]=max(h[st.top()],nxt[st.top()]);
            st.push(i);
        }
        int ans=0;
        int prv=0;
        for(int i=0;i<n;i++){
            int ht=min(prv,nxt[i]);
            ans+=max(0,ht-h[i]);
            prv=max(prv,h[i]);
        }
        return ans;
    }
};