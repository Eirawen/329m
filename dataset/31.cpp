class Solution {
public:
    int trap(const vector<int>& height) {

        unordered_map<int, int> depths_counter;
        priority_queue<int, vector<int>, less<>> pq;

        int current_max = 0;
        int total_trapped_water = 0;

        for (size_t i = 0; i < height.size(); ++i) {
            if (current_max > height[i]) {
                const int depth = current_max - height[i];

                if (depths_counter.contains(depth) && depths_counter[depth] > 0) {
                    depths_counter[depth]++;
                } else {
                    depths_counter[depth] = 1;
                    pq.push(depth);
                }
            }

            while (pq.size() && current_max - pq.top() < height[i]) {
                const int depth = pq.top();
                pq.pop();

                const int trapped_depth = depth - (current_max - min(current_max, height[i]));
                total_trapped_water += trapped_depth * depths_counter[depth];

                if (trapped_depth < depth) {
                    const int remaining_depth = depth - trapped_depth;
                    if (depths_counter.contains(remaining_depth) && depths_counter[remaining_depth] > 0) {
                        depths_counter[remaining_depth] += depths_counter[depth];
                    } else {
                        depths_counter[remaining_depth] = depths_counter[depth];
                        pq.push(remaining_depth);
                    }
                }

                depths_counter[depth] = 0;
            }

            current_max = max(current_max, height[i]);
        }

        return total_trapped_water;
    }
};