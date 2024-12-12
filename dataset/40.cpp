class Solution {
public:
    vector<int> LGE(vector<int>& height,int n){
        vector<int> left(n,0);
        stack<int> st;
        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>st.top()){
                st.pop();
            }
            if(st.empty()){
                left[i]=0;
                st.push(height[i]);
            }
            else{
                left[i]=st.top();
            }
        }
        return left;
    }
    vector<int> RGE(vector<int>& height,int n){
        vector<int> right(n,0);
        stack<int> st;
        for(int i=n-1;i>=0;i--){
            while(!st.empty() && height[i]>st.top()){
                st.pop();
            }
            if(st.empty()){
                right[i]=0;
                st.push(height[i]);
            }
            else{
                right[i]=st.top();
            }
        }
        return right;
    }


    int trap(vector<int>& height) {
        int n=height.size();
        int totalCapacity=0,capacity=0;
        vector<int> left,right;
        left=LGE(height,n);
        right=RGE(height,n);

        for(int i=0;i<n;i++){
            capacity=min(left[i],right[i])-height[i];
            if(capacity>0){
                totalCapacity+=capacity;
            }
        }
        return totalCapacity;
    }
};