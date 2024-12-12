class Solution {
public:
    int trap(vector<int>& height) {
        vector<vector<int>> decision_pillars;
        int max_height = 1;
        for(int i=0; i<height.size(); i++){
            int curr = height[i];
            if(curr >= max_height){
                max_height = curr;
                decision_pillars.push_back({curr, i});
            }
        }
        if(decision_pillars.empty()){
            return 0;
        }
        int max_index = decision_pillars.size() - 1;
        stack<vector<int>> decision_pillars_right;
        max_height = 1;
        for(int i=height.size()-1; i>=decision_pillars[max_index][1]; i--){
            int curr = height[i];
            if(curr >= max_height){
                max_height = curr;
                decision_pillars_right.push({curr, i});
            }
        }
        // for(int i=decision_pillars[max_index][1]+1; i<height.size(); i++){
        //     int curr = height[i];
        //     if(curr <= max_height){
        //         max_height = curr;
        //         decision_pillars.push_back({curr, i});
        //     }
        // }
        int water_content = 0;
        for(int i=0; i<max_index; i++){
            int water_level = decision_pillars[i][0];
            int start = decision_pillars[i][1];
            int end = decision_pillars[i+1][1];
            for(int j=start+1; j<end; j++){
                water_content += (water_level - height[j]);
            }
        }
        while(decision_pillars_right.size() > 1){
            int start = decision_pillars_right.top()[1];
            decision_pillars_right.pop();
            int water_level = decision_pillars_right.top()[0];
            int end = decision_pillars_right.top()[1];
            for(int j=start+1; j<end; j++){
                water_content += (water_level - height[j]);
            }
        }
        return water_content;
    }
};