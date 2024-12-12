class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<array<int, 2>> ascendingVals;
        ascendingVals.push({target[0], 0});

        int n = target.size();
        int ans = 0;
        for (int i = 1; i < n; i++) {
            int num = target[i];
            while (!ascendingVals.empty() && target[ascendingVals.top()[1]] > num) {
                auto [prev, prevIdx] = ascendingVals.top();
                int diff = target[prevIdx] - num;
                ans += min(prev, diff);
                ascendingVals.pop();
            }
            if (ascendingVals.empty() || target[ascendingVals.top()[1]] < num) {
                int lastHeight = ascendingVals.empty() ? 0 : target[ascendingVals.top()[1]];
                ascendingVals.push({target[i] - lastHeight, i});
            }
        }
        while (!ascendingVals.empty()) {
            ans += ascendingVals.top()[0];
            ascendingVals.pop();
        }
        return ans;
    }
};