class Solution {
public:
    // O(n) time | O(n) space
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        int operations = 0;
        stack<pair<int, int>> monostack; // {height, work needed}
        monostack.push({0, 0});

        for (int i = 0; i <= n; ++i) {
            int height =
                i < n ? target[i] : INT_MAX; // INT_MAX to force stack collapse
                                             // at end, if needed
            int work = max(0, height - monostack.top().first);
            while (monostack.size() && height > monostack.top().first) {
                operations += monostack.top().second;
                monostack.pop();
            }
            monostack.push({height, work});
        }
        return operations;
    }
};