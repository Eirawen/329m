class Solution {
private:
    void findLeftLargestElement( vector<int> &leftLargestElement, int start, int end, vector<int> &height){

        stack<int> st;

        for(int i=start; i<=end; i++){
            if( !st.empty() && height[i] < st.top() ) leftLargestElement[i] = st.top();
            else{
                while( !st.empty() && height[i]>=st.top() ){
                    st.pop();
                }
                if( st.empty() ) leftLargestElement[i] = -1;
                else leftLargestElement[i] = st.top();
                st.push( height[i] );
            }
            
        }
        return;
    }

    void findRightLargestElement( vector<int> &rightLargestElement, int start, int end, vector<int> &height){

        stack<int> st;

        for(int i=end; i>=start; i--){
            
            if( !st.empty() && height[i] < st.top() ) rightLargestElement[i] = st.top();
            else{
                while( !st.empty() && height[i]>=st.top() ){
                    st.pop();
                }
                if( st.empty() ) rightLargestElement[i] = -1;
                else rightLargestElement[i] = st.top();
                st.push( height[i] );
            }
            
            
        }
        return;
    }
public:
    int trap(vector<int>& height) {
        int n = height.size();

        int maxWaterSum = 0;

        vector<int> leftLargestElement(n, -1);
        vector<int> rightLargestElement(n, -1);

        findLeftLargestElement( leftLargestElement, 0, n-1, height);
        findRightLargestElement( rightLargestElement, 0, n-1, height);

        for(int i=0; i<n; i++){
            // cout << " leftLargestElement " << leftLargestElement[i] << " rightLargestElement " << rightLargestElement[i] << endl;
            if( leftLargestElement[i]!=-1 && rightLargestElement[i]!=-1){
                maxWaterSum +=( min( leftLargestElement[i], rightLargestElement[i]) - height[i]);
            }
        }
        return maxWaterSum;
    }

    
};



// class Solution {
// public:
//     int trap(vector<int>& height) {
    // o(n^2) solution
//         int n = height.size();

//         int maxWaterSum = 0;

//         for(int i=0; i<n; i++){
//             int maxLeftVal = 0;
//             for(int left =0; left<=i; left++){
//                 maxLeftVal = max(maxLeftVal, height[left]);
//             }
//             int maxRightVal = 0;
//             for(int right =i; right<n; right++){
//                 maxRightVal = max(maxRightVal, height[right]);
//             }

//             int minHeightContain = min( maxLeftVal, maxRightVal);
//             maxWaterSum += (minHeightContain - height[i]);
//         }

//         return maxWaterSum;
//     }

    
// };