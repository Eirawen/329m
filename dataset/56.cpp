class Solution {
public:

    bool is_poss(int mid, vector<int>&nums)
    {
        int n = nums.size();
        int mini = nums[0] , ans = nums[0];

        for(int i = 1; i < n; i++){

            if(nums[i] <= mini){
                mini = min(mini , nums[i]);
            }

            else{
                ans += (nums[i] - mini);
                mini = nums[i];
            }
        }

        return ans <= mid;
    }

    int minNumberOperations(vector<int>& nums) {
        
        int n = nums.size();

        long low = 1 , high = 1e12 , ans = 0;

        while(low <= high)
        {
            int mid = (low + high) >> 1;

            if(is_poss(mid, nums)){
                ans = mid;
                high = mid-1;
            }

            else low = mid+1;
        }

        return ans;
    }
};