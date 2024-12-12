class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        /*remove 
        int n=target.size();
        int l=0; 
        int rs=0;
        for(int i=0;i<n;i++){
            if(target[i]<l){
                rs+=l-target[i]; 
            }
            
            l=target[i];
        }
         rs+=l;
        return rs;
        */
        //add
        int n=target.size();
        if(n==0) return 0;
        int ans=target[0];
        for(int i=1;i<n;i++){
            if(target[i]>target[i-1]){
                ans+=target[i]-target[i-1];
            }
        }
        return ans;
    }
};