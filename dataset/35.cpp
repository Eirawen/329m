class Solution {
public:
    int trap(vector<int>& height) {
        auto llist = std::vector<int>();
        for (int i = 0; i < height.size(); ++i) {
            if (i == 0) {
                llist.push_back(0);
                continue;
            }
            int potential_water = height[i - 1] - height[i] + llist.back();
            if (potential_water > 0) {
                llist.push_back(potential_water);
            } else {
                llist.push_back(0);
            }
        }

        auto rlist = std::vector<int>();
        for (int i = height.size() - 1; i > -1; --i) {
            if (i == height.size() - 1) {
                rlist.push_back(0);
                continue;
            }
            int potential_water = height[i + 1] - height[i] + rlist.back();
            if (potential_water > 0) {
                rlist.push_back(potential_water);
            } else {
                rlist.push_back(0);
            }
        }

        std::reverse(rlist.begin(), rlist.end());

        auto result = std::vector<int>();
        for (int i = 0; i < height.size(); ++i) {
            int min = llist[i] < rlist[i] ? llist[i] : rlist[i];
            result.push_back(min);
        }

        int sum = std::accumulate(result.begin(), result.end(), 0);
        return sum;
    }
};