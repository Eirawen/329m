class Solution {
public:
    int trap(vector<int>& height) {

        int n = height.size();
        int maxHeight = INT_MIN;
        int maxInd = -1;

        for(int i =0 ;i<n;i++){
            if(maxHeight<height[i]){
                maxHeight = height[i];
                maxInd = i;
            }
        }


        int water=0;
        int rightmax=0;
        int leftmax=0;

        for(int i=0; i<maxInd; i++){
            if(height[i]<= leftmax){
                water += leftmax- height[i];
            }
            else{
                leftmax= height[i];
            }
        }

        for(int i=n-1; i>maxInd; i--){
            if(height[i]<= rightmax){
                water += rightmax- height[i];
            }
            else{
                rightmax= height[i];
            }
        }

        return water;
    }
};