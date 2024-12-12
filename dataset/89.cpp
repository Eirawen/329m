class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> s;
        s.push(target[0]);
        int n = target.size();
        int res = target[0];
        for(int i = 1; i < n;i++){
             if(s.top() < target[i]){
                res= res+target[i]-s.top();
             }
             s.push(target[i]);
        }
        return res;
    }
};