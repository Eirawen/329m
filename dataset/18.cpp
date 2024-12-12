class Solution {
public:
    int maxL(vector<int>& height , int target){
        if(target == 0) return 0;
        int highest = -10000;
        for(int i = 0; i < target; i++){
            highest = max(highest , height.at(i));
        }
        return highest;
    }
    int maxR(vector<int>& height , int target){
        if(target == height.size() - 1) return 0;
        int highest = -10000;
        for(int i = target + 1; i < height.size(); i++){
            highest = max(highest , height.at(i));
        }
        return highest;
    }
    int trap(vector<int>& nums) {
        int R = 0;
        map<int , int> highMap;
        for(int i = nums.size() - 1; i > 0; i--){
            R = max(R , nums.at(i));
            highMap[i] = R;
        }
        int result = 0;
        int L = 0;
        for(int i = 0; i < nums.size(); i++){
            int score = min(L , highMap[i]) - nums.at(i);
            if(score > 0) result += score;
            L = max(L , nums.at(i));
        }
        return result;
    }
};