class Solution {
public:
    vector<int> dpl,dpr;
    int trap(vector<int>& height) {
        dpl.push_back(0);
        int maxl=height[0];
        for(int i=1;i<height.size();i++){
            dpl.push_back(maxl);
            maxl=max(maxl,height[i]);
        }
        for(int i=0;i<height.size();i++){
            dpr.push_back(0);
        }
        int maxr=height[height.size()-1];
        
        for(int i=height.size()-2;i>=0;i--){
            dpr[i]=maxr;
            maxr=max(maxr,height[i]);
        }

        int ans=0;
        for(int i=0;i<height.size();i++){
            int lvl=min(dpl[i],dpr[i]);
            if(height[i]<lvl)
            ans+=(lvl-height[i]);
        }

        return ans;
    }
};