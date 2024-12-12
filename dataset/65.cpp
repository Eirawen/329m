class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        stack<pair<int,int>> s;
        s.push({0,0});
        int ops = 0;
        for(int i=0; i<=n; i++){
            int height = i<n ? target[i] : INT_MAX;
            int work = max(height-s.top().first, 0);
            while(!s.empty() && s.top().first < height){
                ops+=s.top().second;
                s.pop();
            }
            s.push({height, work});
        }
        return ops;

    }
};

// 3 1 5 4 2
// 2 0 4 3 1
// 1 0 3 2 0
// 0 0 2 1 0

// 2 1 1 2 1

// 1 4 2