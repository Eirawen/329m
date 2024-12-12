class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> s;
        int ans = 0;
        for(int i = 0; i < target.size(); i++){
            if((s.empty()) || (target[i] > s.top())){
                s.push(target[i]);
            } else if(!s.empty() && target[i] < s.top()){
                while(!s.empty() && target[i] < s.top()){
                    auto topEl = s.top();
                    s.pop();
                    if(s.size() > 0){
                        ans += topEl - max(s.top(), target[i]);
                    } else {
                        ans += topEl - target[i];
                    }
                }
                if((s.empty()) || (target[i] > s.top())){
                    s.push(target[i]);
                }
            }
        }
        if(!s.empty())
            ans += s.top();
        return ans;
    }    
};