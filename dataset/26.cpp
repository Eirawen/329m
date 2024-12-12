class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        // Số cột <= 2 chắc chắn không giữ được nước
        if (n <= 2) {
            return 0;
        }
        // Tìm các cột cực đại (Cao nhất so với các cột lân cận)
        vector<int> temp; // Lưu trữ các cột cực đại
        if (height[0] >= height[1]) {
            temp.push_back(0);
        }
        for (int i = 1; i < n; i++) {
            // Điều kiện đảm bảo 
            if (height[i] >= height[i - 1] && (i == n - 1 || height[i] >= height[i + 1])) { 
                temp.push_back(i);
            }
        }

        int count = 1;
        while (count != 0) {
            for (int i = 1; i < temp.size() - 1; i++) {
                int left = temp[i - 1];
                int right = temp[i + 1];
                if (height[temp[i]] <= min(height[left], height[right])) {
                    temp.erase(temp.begin() + i);
                    i--; // Lùi lại để kiểm tra lại đỉnh sau khi xóa
                }
            }
            count = 0;
            for (int i = 1; i < temp.size() - 1; i++) {
                int left = temp[i - 1];
                int right = temp[i + 1];
                if (height[temp[i]] <= min(height[left], height[right])) {
                    count++;
                    break;
                }
            }
        }

        int kq = 0;
        for (int i = 0; i < temp.size() - 1; i++) {
            int left = temp[i];
            int right = temp[i+1];
            int min;
            if (height[left] < height[right]) {
                min = height[left];
            } else {
                min = height[right];
            }
            // Cong nuoc o cac cot giua
            for (int j = left + 1; j < right; j++) {
                if (height[j] < min) {
                    kq += (min - height[j]);
                }
            }
        }
        return kq;
    }
};