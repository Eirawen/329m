class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        vector<int> nse(n+1, n);

        stack<int> s;
        for (int i = 0; i < n; ++i) {
            int t = target[i];
            while (!s.empty() && target[s.top()] > t) {
                nse[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        stack<pair<int, int>> active;
        vector<int> pending(n+1, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            // Remove current st-top if reqd.
            while (!active.empty() && active.top().second <= i) {
                active.pop();
            }

            int leftSweep = 0, ind = -1;
            if (!active.empty()) {
                leftSweep = active.top().first;
                ind = active.top().second;
            }

            // cout << "i ANS pending: " << i << " " << ans << " " << pending[i] << "\n";

            // cout << "i leftSweep{f s} tgt: " << i << " {" << leftSweep << ", " << ind << "} " << target[i] << "\n";
            
            if (target[i] <= leftSweep) {
                // cout << "Continuing as tgt < leftSweep " << i << "\n";
                continue;
            }
            
            // Perform a sweep otherwise
            if (nse[i] == n) {
                // there is no next smaller int
                ans += target[i] - leftSweep;
                // cout << "No NSE\n";
            } else {
                int op = target[i] - max(leftSweep, target[nse[i]]);
                ans += op;
                pending[nse[i]] = target[nse[i]];
                // cout << "op NSE: " << op << " " << nse[i] << "\n";
            }
            active.push({target[i], nse[i]});
        }

        return ans;
    }
};


/**
[9,5,3,7,10,10,2,8,9,4,8]
2: [7,3,1,5,8,8,0,6,7,2,6]
1, 2: [6,2,0,4,7,7,0,4,5,0,4]

2 + 4
4 + 3
4 + 1
4


5 + 6 + 7 + 5 + 5



4
2
1
4
3 = 14

**/