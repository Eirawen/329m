class Solution {
public:
    int trap(vector<int>& arr) {
        int l=0, r=arr.size()-1, water=0;
        int lmax=0, rmax=0;
        while(l<r){
            if(arr[l]<=arr[r]){
                if(lmax>arr[l]){
                    water+=lmax-arr[l];
                }
                else{
                    lmax=arr[l];
                }
                l++;
            } else {
                if(rmax>arr[r]){
                    water+=rmax-arr[r];
                }
                else{
                    rmax=arr[r];
                }
                r--;
            }
        }
        return water;
    }
};