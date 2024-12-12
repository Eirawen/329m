class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int>leftMostLargest(n);
        vector<int>rightMostLargest(n);
        int maxi = height[0];
        leftMostLargest[0] = maxi;
        for(int i = 1;i<n;i++){
            maxi = max(maxi,height[i]);
            leftMostLargest[i] = maxi;
        }
        maxi = height[n-1];
        rightMostLargest[n-1] = maxi;
        for(int i = n-2;i>=0;i--){
            maxi = max(maxi,height[i]);
            rightMostLargest[i] = maxi;
        }
        int res = 0;
        for(int i = 1;i<n-1;i++){
            if(leftMostLargest[i] > height[i] && rightMostLargest[i] > height[i]){
                cout<<i<<endl;
                res += (min(leftMostLargest[i],rightMostLargest[i])) - height[i];
            }
        }
        return res;
    }
};