class Solution {
public:
    int trap(vector<int>& height) {
        // Số cột <= 2 chắc chắn không giữ được nước
        if (height.size() <= 2) {
            return 0;
        }
        // Tìm các cột cực đại (Cao nhất so với các cột lân cận)
        vector<int> temp; // Lưu trữ các cột cực đại
        for (int i = 0; i < height.size(); i++) {
            // Điều kiện đảm bảo nếu cột đầu thấp hơn cột 2 thì không lấy, cột cuối thấp hơn cột áp cuối thì không lấy
            // Mặc dù Xét từ i = 0 và height[i - 1] nhưng do đặt trước đó là điều kiện "i == 0" với toán tử "||" nên diều kiện tiếp theo không cần phải xét đến
            if ((i == 0 || height[i] >= height[i - 1]) && (i == height.size() - 1 || height[i] >= height[i + 1])) { 
                temp.push_back(i);
            }
        }

        // Loại bỏ những cột không cần thiết (Có độ cao nhỏ hơn hoặc bằng cả 2 cột kế trái và phải), những cột này làm bị thiếu khi tính lượng nước
        // Ở đây phải kiểm tra nhiều lần do do khi xóa rồi thi các cột mới vẫn có thể vi phạm
        // Kiểm tra ở đây còn chưa chặt nên sau khi đúng rồi thì 
        int count = 1;
        while (count != 0) {
            count = 0;
            for (int i = 1; i < temp.size() - 1; i++) {
                int left = temp[i - 1];
                int right = temp[i + 1];
                if (height[temp[i]] <= min(height[temp[i-1]], height[temp[i+1]])) {
                    temp.erase(temp.begin() + i);
                    i--; // Lùi để kiểm tra lại đỉnh sau khi xóa
                    count = 1;
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