class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        int level;
        
        int run_vol = 0; int start = 0;
        int vol = 0;
        bool inCup = false;
        for(int i=0; i<n; i++) {
            if(!inCup && height[i] > 0) {
                inCup = true;
                level = height[i];
            } else if(inCup) {
                if(height[i] >= level) {
                    // Cup changes.
                    vol += run_vol;
                    start = i;
                    //printf("%d\n", run_vol);
                    run_vol=0;
                    level = height[i];
                } else {
                    run_vol += level-height[i];
                }
            }
        }
        // Adjust the end volume if needed.
        if(run_vol > 0) {
            // Go from back to front.
            inCup = false; run_vol = 0;
            //if(start == 0)  return 0;
            bool okay_to_commit = false;
            for(int i=n-1; i>=start; i--) {
                printf("%d ", i);
                if(!inCup) {
                    if(i >= 1 && height[i-1] < height[i]) {
                        inCup = true;
                        level = height[i];
                    }
                } else {
                    if(height[i] <= level) {
                        okay_to_commit = true;
                        run_vol += (level-height[i]);
                    } else {
                        if(okay_to_commit)
                            vol += run_vol;
                        run_vol = 0;
                        okay_to_commit = false;
                        level = height[i];
                    }
                }
            }
            return vol;
        }
        return vol;
    }
};