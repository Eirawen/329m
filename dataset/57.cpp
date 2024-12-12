auto _ = []() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int size = target.size();
        stack<int> s;

        s.push(0);
        vector<int> smallerLeft(size, 0);
        for (int i = 0; i < size; i++) {
            while (target[i] < s.top())
                s.pop();
            smallerLeft[i] = s.top();
            s.push(target[i]);
        }

        s = stack<int>();
        vector<int> smallerRight(size, 0);
        s.push(0);
        for (int i = size - 1; i >= 0; i--) {
            while (target[i] <= s.top())
                s.pop();
            smallerRight[i] = s.top();
            s.push(target[i]);
        }

        int ops = 0;
        for (int i = 0; i < size; i++)
            ops += target[i] - max(smallerLeft[i], smallerRight[i]);
        return ops;
    }
};