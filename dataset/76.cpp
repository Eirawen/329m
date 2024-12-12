class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> increasingHeights;
        int ops = 0;
        for (int height: target) {
            int maxHeight = height;
            while (increasingHeights.size() && increasingHeights.top() >= height) {
                maxHeight = max(maxHeight, increasingHeights.top());
                increasingHeights.pop();
            }
            ops += maxHeight - height;
            increasingHeights.push(height);
        }

        if (increasingHeights.size()) {
            ops += increasingHeights.top();
        }
        
        return ops;
    }
};