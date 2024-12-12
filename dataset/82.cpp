class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> S;

        int ans = 0;

        for (int i = 0; i < target.size(); i++){
            int x = target[i];

            if (S.empty()){
                S.push(x);
            }else if (S.top() == x){
                continue;
            }else if (S.top() < x){
                S.push(x);
            }else{
                int value = S.top()-x;
                ans += value;

                S.top() = x;
            }
        }

        if (S.empty()){
            return ans;
        }

        int t = S.top();

        while (!S.empty()){
            S.pop();

            if (S.empty()){
                int val = t;
                ans += val;
                break;
            }

            int val = (t - S.top());
            ans += val;
            
            t = S.top();
        }

        return ans;
    }
};