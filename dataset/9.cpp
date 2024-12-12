class Solution {
public:
    int trap(vector<int>& height) {
        int mini = 1 << 30, maxi = -1;
        map<int, set<int>> hPos;
        // map<int, vector<int>> hPos;

        for (int i = 0; i < height.size(); i++) {
            if (height[i])
                hPos[height[i]].insert(i);
        }
        if (hPos.empty())
            return 0;
        if (hPos.rbegin()->second.size() == 1 ) {
            if(hPos.size() == 1) return 0;
            auto it = hPos.rbegin();
            auto temp = it->second.begin();
            advance(it, 1);
            height[*temp] = it->first;
            it->second.insert(*temp);
            advance(it, -1);
            hPos.erase(it->first);
        }
        int res = 0;
        auto it = hPos.rbegin();
        auto l = it->second.begin();
        int left = *l;
        auto r = it->second.rbegin();
        int right = *r;
        res += (it->first) * (right - left - 1);
        for (int i = left + 1; i < right; i++) {
            res -= height[i];
        }
        it = hPos.rbegin();
        advance(it, 1);
        for (; it != hPos.rend() && (left >= 0 || right <=height.size()); it++) {
        
            l = it->second.begin();
            int left2 = *l;
            r = it->second.rbegin();
            int right2 = *r;
            // cout<<"Outer LOOP: "<<res<<endl;
            // cout<<left<<" "<<right<<" "<<endl;
            // cout<<left2<<" "<<right2<<" "<<endl;
            if(left2 < left || right2 < left) {
                res += (left - left2 - 1) * (it->first);
                for (int i = left2+1; i < left; i++) {
                    res -= height[i];
                }
                left = left2;
                // cout<<"Left LOOP: "<<res<<endl;
                // cout<<left<<" "<<right<<" "<<endl;
                // cout<<left2<<" "<<right2<<" "<<endl;
            }
            if(right2 > right || left2 > right) {
                res += (right2 - right - 1) * (it->first);
                for (int i = right+1; i < right2; i++) {
                    res -= height[i];
                }
                // cout<<"Right LOOP: "<<res<<endl;
                // cout<<left<<" "<<right<<" "<<endl;
                // cout<<left2<<" "<<right2<<" "<<endl;
                right = right2;
            }
        }
        return res;
    }
};