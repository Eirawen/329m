class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> water = {};
        int curr_val = 0;
        for (int level : height) {
            if (level < curr_val) {
                water.push_back(curr_val - level);
            }
            else {
                curr_val = level;
                water.push_back(0);
            }
        }
        curr_val = 0;
        int sum_val = 0;
        for (int ind = height.size() - 1; ind >= 0; --ind) {
            if (height[ind] < curr_val) {
                sum_val += min(water[ind], (curr_val - height[ind]));
            }
            else {
                curr_val = height[ind];
                cout << 0;
            }
        }
        return sum_val;
    }
};