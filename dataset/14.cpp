class Solution {
public:
    int trap(vector<int>& height) {
        int volume = 0;
        int n = height.size();

        if (n < 3)
            return volume;

        int maxHeight = height[0];
        int currHeight;
        int currVolume = 0;

        for(int i = 1; i < n; i++)
        {
            currHeight = height[i];
            if (currHeight >= maxHeight)
            {
                volume += currVolume;
                currVolume = 0;
                maxHeight = currHeight;
            }
            else
            {
                currVolume += maxHeight - currHeight;
            }
        }

        maxHeight = height[n - 1];
        currVolume = 0;
        for(int i = n - 2; i >= 0; i--)
        {
            currHeight = height[i];
            if (currHeight > maxHeight)
            {
                printf("i=%d currHeight=%d maxHeight=%d currVolume=%d\n", i, currHeight, maxHeight, currVolume);
                volume += currVolume;
                currVolume = 0;
                maxHeight = currHeight;
            }
            else
            {
                // printf("i=%d currHeight=%d maxHeight=%d\n", i, currHeight, maxHeight);
                currVolume += maxHeight - currHeight;
            }
        }

        return volume;
    }
};