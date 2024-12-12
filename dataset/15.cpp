class Solution {
public:
    bool isOverlapping(pair<int,int> &in1, pair<int,int> &in2) {
        if((in1.first>= in2.first && in1.second<=in2.second)) return true;
        if((in1.first<= in2.first && in1.second>=in2.second)) return true;
        return false;
    }
    void mergeInterval(vector<pair<int,int>> &vi, pair<int,int> &in) {
        int n= vi.size();
        if(n==0) {
            vi.push_back(in); return;
        }
        pair<int,int> last = vi[n-1];
        while(isOverlapping(last, in)) {
            vi.pop_back();
            in= make_pair(min(in.first, last.first), max(in.second, last.second));
            if(vi.size()==0) break;
            n--;
            last = vi[n-1];
        }
        vi.push_back(in);
    }

    int trap(vector<int>& v) {
        int n=v.size(), i, j, k, vol=0;
        vector<int> prefSum(n+1,0);
        for(i=0;i<n;i++) {
            prefSum[i+1] = v[i]+prefSum[i];
        }
        
        stack<pair<int,int>> st;
        vector<pair<int,int>> intervals;
        pair<int,int> t;
        for(i=1;i<n;i++) {
            if(v[i] < v[i-1]) {
                st.push(make_pair(v[i-1], i-1));
                continue;
            }
            if(st.empty()) continue;
            while(!st.empty()) {
                t = st.top();
                if(t.first > v[i]) break;
                st.pop();
            }
            pair<int,int> intval = make_pair(t.second, i);
            // cout<<t.second<<" "<<i<<endl;
            mergeInterval(intervals, intval);
        }

        for(auto x: intervals) {
            cout<<x.first<<" "<<x.second<<endl;
        }

        for(auto x: intervals) {
            int st = x.first, en= x.second;
            vol+= min(v[st], v[en])*(en-st-1) - (prefSum[en]-prefSum[st+1]);
        }
        return vol;
    }
};