class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        vector<int> left,right;
        int n = target.size();
        stack<int> s;
        s.push(target[0]);
        left.push_back(-1);
        for (int i = 1 ; i < n ; i++) {
            while (!s.empty() && s.top() > target[i]) s.pop();
            if (s.empty()) {
                left.push_back(-1);
            } else {
                left.push_back(s.top());
            }
            s.push(target[i]);
        }
        while(!s.empty()) s.pop();
        s.push(target[n-1]);
        right.push_back(-1);
        for (int i = n-2 ; i>=0 ; i--) {
            while (!s.empty() && s.top() >= target[i]) s.pop();
            if (s.empty()) {
                right.push_back(-1);
            } else {
                right.push_back(s.top());
            }
            s.push(target[i]);
        }
        reverse(right.begin(), right.end());
        int minOp = 0;
        for (int i = 0 ; i < n ; i++) {
            int reqOp = max(left[i], right[i]);
            if (reqOp == -1) {
                minOp += target[i];
            } else {
                minOp += (target[i] - reqOp);
            }
        }
        return minOp;
    }
};