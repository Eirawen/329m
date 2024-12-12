// class Solution {
//     int steps = 0;
// public:
//     int minNumberOperations(vector<int>& target) {
//         minus_lowest_for_all(target, 0, target.size() - 1);
//         return steps;
        
//     }
//     void minus_lowest_for_all(vector<int>& target, int start, int end){
//         if(start == end){
//             steps += target[start];
//             return;
//         }
//         vector<int> min_ids;
//         for(int i = start; i <= end; i++){
//             if(min_ids.empty() ||  target[i] == target[min_ids[0]]){
//                 min_ids.push_back(i);
//             }else if(target[i] < target[min_ids[0]]){
//                 min_ids.clear();
//                 min_ids.push_back(i);
//             }

//         }
//         // printf("min idx is %d", min_ids[0]);
//         steps += target[min_ids[0]];
//         int to_minus = target[min_ids[0]];
//         // printf("current steps is %d\n", steps);
//         for(int i = start; i <= end; i++){
//             target[i] -= to_minus;
//             // printf("target %d is [%d]", i , target[i]);
//         }
        

//         int next_s = start;
//         for(auto iter : min_ids){
//             if(next_s < iter){
//                 minus_lowest_for_all(target, next_s,iter-1);

//             }
//             next_s = iter + 1;
//         }
//         if(min_ids[min_ids.size() -1] < end){
//             minus_lowest_for_all(target, min_ids[min_ids.size() -1] +1, end);
//         }
//     }
// };
// class Solution {
// public:
//     int minNumberOperations(vector<int>& target) {
//         int noOfOperations = target[0];
//         for(int i = 1; i < target. size(); i++) {
//             if(target[i] > target[i-1]) 
//                 noOfOperations += (target[i]-target[i-1]);
//         }
//         return noOfOperations;
//     }
// };

class Solution {
public:
    // O(n) time | O(n) space
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        int operations = 0;
        stack<pair<int,int>> monostack; // {height, work needed}
        monostack.push({0, 0});

        for (int i = 0; i <= n; ++i) {
            int height = i < n ? target[i] : INT_MAX; // INT_MAX to force stack collapse at end, if needed
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