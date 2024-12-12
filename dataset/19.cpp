class Solution {
public:
  unordered_map<int,int>next; 
  unordered_map<int,int>prev;
    int trap(vector<int>& height) {
        nextGE(height);
        prevGE(height);
        int ans=0;
        for(int i=0;i<height.size();i++)
        {
          if((min(next[i],prev[i]))!=-1)
            ans+=(min(next[i],prev[i])-height[i]);
        }
        return ans;
    }
    void nextGE(vector<int>& nums2) {
       stack<int>s;
       for(int i=nums2.size()-1;i>=0;i--){
            while(!s.empty()){
                if(s.top()<=nums2[i])
                s.pop();
                else
                break;
            }
          if(s.empty())
          {next[i]=-1; s.push(nums2[i]);}
          else
          next[i]=s.top();
         
        } 
    }
    void prevGE(vector<int>& nums2) {
       stack<int>s;
       for(int i=0;i<nums2.size();i++){
            while(!s.empty()){
                if(s.top()<=nums2[i])
                s.pop();
                else
                break;
            }
          if(s.empty())
         { prev[i]=-1;s.push(nums2[i]);}
          else
          prev[i]=s.top();
          
        } 
    }
};