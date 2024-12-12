class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int operations = target[0];
        for (int i = 1; i < target.size(); ++i) {
            if (target[i] > target[i - 1]) {
                operations += target[i] - target[i - 1];
            }
        }
        return operations;
    }
};
// class Solution {
// public:
//     int minNumberOperations(vector<int>& target) {
//         stack<int> st;
//         int operations = 0;
//         for (int num : target) {
//             if (st.empty() || num > st.top()) {
//                 operations += num - (st.empty() ? 0 : st.top());
//             }
//             st.push(num);
//         }
//         return operations;
//     }
// };