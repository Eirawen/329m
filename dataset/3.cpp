class Solution {
public:
    int trap(vector<int>& height) {
        

        // Two Pointers
        int l=0;
        int r=height.size()-1;

        // Find left/right initial max height
        while(l<r && height[l]<=height[l+1]) l++;
        while(l<r && height[r]<=height[r-1]) r--;

        // Accumulate water
        int ans=0;
        while(l<r){
            // Memorize current leftMax & rightMax
            int leftMax = height[l];
            int rightMax = height[r];
            cout<<"leftMax "<<leftMax << " rightMax "<<rightMax<<endl;
            if(leftMax <= rightMax){
                // Add from left
                while(l<r && leftMax >height[++l]){
                    ans += leftMax - height[l];
                }
            }else{
                // Add from right
                while(l<r && rightMax > height[--r]){
                    ans += rightMax-height[r];
                }
            }
        }
        return ans;
    }
};