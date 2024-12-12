class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        
        int res = 0;
        vector<int> st{};
        
        for(const auto v : target) {
            
            if (!st.empty() && st.back() > v) {
                res += st.back() - v;
                while (!st.empty() && st.back() > v) {
                    st.pop_back();
                }
            }
            
            if(st.empty() || st.back() < v) {
                st.push_back(v);
            }
        }
        
        res += st.back();
        
        return res;
    }
};

/*
[1,2,3,2,1]
[3,1,1,2]
[3,1,5,4,2]
[3,4,2,5,6]

[100,1,5,4,111]
*/