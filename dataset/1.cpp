class Solution {
public:
    int trap(vector<int>& height) {
        int totalWater = 0;
        int currHeight = height[0];
        int currIdx = 0;

        for(unsigned i = 1; i < height.size() - 1; ++i)
        {
            if(height[i] >= currHeight)
            {
                currHeight = height[i];
                currIdx = i;
            }
            else
            {
                totalWater += currHeight - height[i];
            }

        }

        if(height[height.size()-1] < currHeight)
        {
            int secondHeight = height[height.size()-1];
            for(unsigned j = height.size() - 2; j > currIdx; --j)
            {
                if(height[j] >= secondHeight)
                {
                    secondHeight = height[j];
                }

                totalWater -= currHeight - secondHeight;
                printf("Removing Water: %d\n", totalWater);
            }
        }
        
        return totalWater;
    }
};