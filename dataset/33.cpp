class Solution {

    int left[100000];
    int right[100000];
public:
    int trap(vector<int>& height) {

        int n = height.size();

        for(int i=0;i<n;i++)
        {
            left[i]=0;
            right[i]=0;
        }

        int j=n-2;

        left[0]=height[0];
        right[n-1]=height[n-1];

        for(int i=1;i<n;i++)
        {
            left[i]=max(left[i-1], height[i]);
            right[j]=max(right[j+1], height[j]);

            j--;
        }

        int waterTrapped =0;

        for(int i=0;i<n;i++)
        {
            waterTrapped=waterTrapped+max((min(left[i], right[i])-height[i]),0);
        }

        return waterTrapped;
    }
};