class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int n = height.size();
        int l = 0, r = n - 1;
        int lh = 0, rh = 0;
        while (l <= r) {
            if (lh <= rh) {
                if (lh > height[l]) {
                    ans += lh - height[l];
                }
                
                lh = max(lh, height[l]);
                l++;
            } else {
                if (rh > height[r]) {
                    std::cout << "r: " << r << std::endl;
                    ans += rh - height[r];
                }

                rh = max(rh, height[r]);
                r--;
            }
        }

        return ans;
    }
};