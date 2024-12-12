class Solution {
public:
    vector<int> left(vector<int>&arr){
        vector<int>ans;
        int n = arr.size();
        stack<int>st;
        for(int i=0;i<n;i++){
            if(st.empty())ans.push_back(0);
            else{
                while(!st.empty() and st.top()>arr[i])st.pop();
                if(st.empty())ans.push_back(0);
                else ans.push_back(st.top());
            }
            st.push(arr[i]);
        }
        return ans;
    }
    vector<int> right(vector<int>&arr){
        vector<int>ans;
        int n = arr.size();
        stack<int>st;
        for(int i=n-1;i>=0;i--){
            if(st.empty())ans.push_back(0);
            else{
                while(!st.empty() and st.top()>=arr[i])st.pop();
                if(st.empty())ans.push_back(0);
                else ans.push_back(st.top());
            }
            st.push(arr[i]);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    int minNumberOperations(vector<int>& target) {
        vector<int>l = left(target);
        vector<int>r = right(target);
        int n = target.size();
        int ans = 0;
        for(int i=0;i<n;i++){
            ans += target[i]-max(l[i],r[i]);
        }
        return ans;
    }
};