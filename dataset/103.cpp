class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size(), ans = 0, dif = 0;
        for (int i = n - 1; i >= 0; i--) {
            ans += max(0, target[i] - dif);
            dif  = target[i];
        }
        return ans;
    }
};