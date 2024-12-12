class Solution {
public:
    int trap(vector<int>& arr) {
        int n=arr.size();
        int maxTillNow=arr[0];
        int res=0;
        priority_queue<pair<int,int>, vector<pair<int,int>>> pq;
        for(int i=1; i<n; i++){
            pq.push({arr[i], i});
        }
        for(int i=1; i<n; i++){
            pair<int,int> cur = {-1, -1};
            while(!pq.empty()){
                cur = pq.top();
                if(cur.second <= i){
                    pq.pop();
                    cur = {-1, -1};
                }else{
                    break;
                }
            }
            if(cur.second == -1){
                break;
            }
            res += max(0, min(maxTillNow, cur.first) - arr[i]);
            maxTillNow = max(maxTillNow, arr[i]);
        }
        return res;
    }
};