class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        priority_queue<int>pq;
        int op = 0;
        for(int i=0;i<target.size();i++){
            if(!pq.empty() && pq.top()>target[i]){
                int m = pq.top();
                while(!pq.empty() && pq.top()>target[i]){
                    pq.pop();
                }
                op += m - target[i];
            }
            if(!pq.empty() && pq.top()==target[i]){
                // do not fill
            }else{
                pq.push(target[i]);
            }
        }
        if(!pq.empty()) op += pq.top();
        return op;
    }
};