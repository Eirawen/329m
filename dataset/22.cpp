class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<vector<int>> vec(n, vector<int>(3,0));        
        int left_max = 0, right_max = 0;
        for(int i = 0; i<height.size(); i++){
            int r = n-i-1;
            left_max = max(left_max, height[i]);
            right_max = max(right_max, height[r]);
            vec[i][0] = height[i];
            vec[i][1] = left_max;
            vec[r][2] = right_max;
        }
        int res = 0;
        for(auto i : vec){
           // cout << i[0] << "  " << i[1] <<  "    " << i[2] << endl;
            res += min(i[1],i[2]) - i[0];
            //cout << res << endl;
        }
        return res;
    }
};