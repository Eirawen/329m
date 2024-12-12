class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> inflec_p;
        int prev_dx = 0;
        int prev_p = 0;
        // add 0 for right point calculation
        height.push_back(0);
        for (int i = 0; i < height.size(); ++i) {
            int dx = height[i] - prev_p;
            /*
            if (   (prev_dx >= 0 && dx >= 0)
                || (prev_dx <= 0 && dx <= 0)) {

            } else if (prev_dx >= 0 && dx < 0) {
                //peak found
                inflec_p.push_back(i - 1);
            } else if (prev_dx <= 0 && dx > 0) {
                //inflec_p.push_back(-(i - 1));
            } else {
                cout << "Never i " << i << '\n';
            }
            */
            if (prev_dx >= 0 && dx < 0) {
                //peak found
                inflec_p.push_back(i - 1);
            }
            
            prev_dx = dx;
            prev_p = height[i];
        }
        height.pop_back();

        
        for (auto p: inflec_p) {
            cout << p << ", ";
        }
        cout << '\n';
        
        if (inflec_p.size() < 2) {
            return 0;
        }

        int peak_r = inflec_p.size() - 1;
        int peak_l = 0;
        int l = inflec_p[peak_l];
        int r = inflec_p[peak_r];
        int n_peak_l = 1;
        int n_peak_r = -1;

        int volume = 0;
        while (l != r) {
            int peak_l_idx = inflec_p[peak_l];
            int peak_r_idx = inflec_p[peak_r];
            if (height[peak_l_idx] <= height[peak_r_idx]) {
                l++;
                int n_peak_l_idx = inflec_p[peak_l + n_peak_l];
                if (l == n_peak_l_idx) {
                    if (height[n_peak_l_idx] > height[peak_l_idx]) {
                        peak_l += n_peak_l;
                        n_peak_l = 1;
                        continue;
                    } else {
                        n_peak_l += 1;
                    }
                }
                int vol_dx = height[peak_l_idx] - height[l];
                if (vol_dx > 0) {
                    volume += height[peak_l_idx] - height[l];
                }
            } else {
                r--;
                int n_peak_r_idx = inflec_p[peak_r + n_peak_r];
                if (r == n_peak_r_idx) {
                    if (height[n_peak_r_idx] > height[peak_r_idx]) {
                        peak_r += n_peak_r;
                        n_peak_r = -1;
                        continue;
                    } else {
                        n_peak_r -= 1;
                    }
                }
                int vol_dx = height[peak_r_idx] - height[r];
                if (vol_dx > 0) {
                    volume += height[peak_r_idx] - height[r];
                }
            }
        }

        return volume;
    }
};