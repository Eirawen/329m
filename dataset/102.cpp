class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int operationWeCanReUse = target[0];
        int totalOperation = target[0];
        for(int i = 1; i<target.size();i++){
            if(target[i]<= operationWeCanReUse){
                operationWeCanReUse = target[i];
            }else{
                totalOperation += target[i] - operationWeCanReUse;
                operationWeCanReUse = target[i];
            }
        }
        return totalOperation;
    }
};