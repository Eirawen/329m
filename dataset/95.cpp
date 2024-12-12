class Solution {
public:
    int minNumberOperations(vector<int>& target) 
    {
        vector<int>check;
        int demo=0;
        int curr=0,prev=0;

       for(int i=0;i<target.size();i++)
       {
         curr=target[i];
         if(curr>prev)
         demo+=abs(curr-prev);

         prev=curr;
       }

       return demo;
        
    }
};