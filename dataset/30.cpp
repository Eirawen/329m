class Solution {
public:
    int tungphanphai(int dau, int cuoi, vector<int>& height) {
        map<int, int, greater<int>> phai;
        for(int i = dau; i <= cuoi; i++) {
            phai[height[i]] = i;
        }
        int tong = 0;

        for(const auto& p :phai) {
            if(p.second < dau) continue;
            else {
                tong += p.first * (p.second - dau + 1);
                if(p.second == cuoi) return tong;
                else dau = p.second + 1;
            } 
        }
        return tong;
    }
    int tungphantrai(int dau, int cuoi, vector<int>& height) {
       map<int, int, greater<int>> trai;
        for(int i = cuoi; i >= dau; i--) {
            trai[height[i]] = i;
        }
        int tong = 0;

        for(const auto& p :trai) {
            if(p.second > cuoi) continue;
            else {
                tong += p.first * (cuoi - p.second + 1);
                if(p.second == dau) return tong;
                else cuoi = p.second - 1;
            } 
        }
        return tong;
    }

    int trap(vector<int>& height) {
        int dau = 0;
        int cuoi = height.size() - 1;
        int tru = 0;
        while(height[dau] == 0 ) {
            if(dau == cuoi) return 0;
            dau++;
        }
        while(height[cuoi] == 0) {
            cuoi--;
        }
        int max0 = dau;
        for(int i = dau; i <= cuoi; i++) {
            tru += height[i];

            if(height[max0] < height[i]) max0 = i;
            
        } 
        int result = 0;
        if(max0 != cuoi) result += tungphanphai(max0 + 1, cuoi, height);
        if(max0 != dau) result += tungphantrai(dau, max0 - 1, height);
        return result += height[max0] - tru;

    }
};