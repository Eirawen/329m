class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        int n = height.size();
        vector<int>left_largest;
        vector<int>right_largest;
        left_largest.push_back(0);
        right_largest.push_back(0);
        int left = INT_MIN;
        int right = INT_MIN;
        for(int i=1;i<n;i++){
            left = max(height[i-1],left);
            left_largest.push_back(left);
        }
        for(int i=n-2;i>=0;i--){
            right = max(height[i+1],right);
            right_largest.push_back(right);
        }
        reverse(right_largest.begin(),right_largest.end());
        vector<int>mini(n);
        for(int i=0;i<n;i++){
            mini[i] = min(left_largest[i], right_largest[i]);
        }

        for(int i=0;i<n;i++){
            int temp = mini[i] - height[i];
            
            if(temp > 0 ) sum+=temp;
        }
        return sum;
    }
};