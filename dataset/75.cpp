class Solution {
public:
    int minNumberOperations(vector<int>& v) {
        v.push_back(0);
        int n = v.size();
        int t = 0;
        stack<int> s;
        s.push(0);
        for (int i=0; i<n; ++i){
            if (v[i]<s.top()){
                int top;
                while (v[i]<s.top()){
                    top = s.top();
                    s.pop();
                    t += (top-max(s.top(), v[i]));
                }
            }
            s.push(v[i]);
        }
        return t;
    }
};