class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n=target.size();
        stack<int>bot;
        bot.push(0);
        int rs=0;
        for(int i=0;i<n;i++){
            if(target[i]<bot.top()){
                rs+=bot.top()-target[i];
                while(target[i]<bot.top()){  
                    bot.pop();
                }
            }
            
            if(target[i]>bot.top()){
                bot.push(target[i]);
            }
        }
        if(!bot.empty()) rs+=bot.top();
        return rs;
    }
};