class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> s;
        int ans = 0;
        for(auto num: target){
            if(s.empty()){
                ans+=num;
            }
            else if(s.top() < num){
                ans+=num-s.top();
            }
            else{
                while(!s.empty()&&s.top()>=num)s.pop();
            }
            s.push(num);
        } 
        return ans;
    }
};