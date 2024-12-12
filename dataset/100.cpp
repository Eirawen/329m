class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int incr = 0, ops = 0, diff = 0;
        for(int i=0; i<target.size(); i++) {
            diff = target[i];
            if (incr > diff) {
                ops += incr-diff;
            }
            incr = diff;
        }
        ops += diff;
        return ops;
    }
};