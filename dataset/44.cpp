class Solution {
public:
    int trap(vector<int>& height) {
        
        int n= height.size();

        vector<int> rightMax(n,0);

        for(int i=n-2;i>=0;i--){
            rightMax[i]=max(rightMax[i+1], height[i+1]);
        }

        // for(int i=0;i<n;i++){
        //     cout<<i<<" "<<rightMax[i]<<endl;
        // }

        int ans=0;
        int leftMax=height[0];
        for(int i=1;i<n;i++){
            int currTrap=  min(leftMax,rightMax[i]) - height[i];
            if(currTrap>0)ans+=currTrap;
            leftMax= max(leftMax,height[i]);
           // cout<<i<<" "<<ans<<endl;
        }

        return ans;
    }
};