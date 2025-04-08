#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
    public:
        long long minAbsoluteSumDiff(vector<long long>& nums1, vector<long long>& nums2) {
            long long n = nums1.size();
    
            if (n == 1) 
                return abs(nums1[0] - nums2[0]);
    
            vector<long long> sorted_nums1 = nums1;
            sort(sorted_nums1.begin(), sorted_nums1.end());
    
            long long original_sum = 0;
            long long max_improvement = 0;
    
            for (long long i = 0; i < n; i++) {
                long long diff = abs(nums1[i] - nums2[i]);
                original_sum += diff;
    
                // 用 lower_bound 來尋找最接近 nums2[i] 的數字
                auto it = lower_bound(sorted_nums1.begin(), sorted_nums1.end(), nums2[i]);
    
                long long new_diff = diff; // 預設為原本的 diff
                if (it != sorted_nums1.end()) {
                    new_diff = min(new_diff, abs(*it - nums2[i]));
                }
                if (it != sorted_nums1.begin()) {
                    new_diff = min(new_diff, abs(*(it - 1) - nums2[i]));
                }
    
                max_improvement = max(max_improvement, diff - new_diff);
            }
    
            long long min_sum_difference = original_sum - max_improvement;
            return min_sum_difference;
        }
};


    
signed main() {
    vector<long long> nums1, nums2;  // 動態大小的 vector
    string line;
    
    // 讀取 nums1
    long long num;
    cin >> num;
    while (cin >> num) {
        nums1.push_back(num);
        if (cin.peek() == '\n') break; // 遇到換行則停止
    }
    
    // 讀取 nums2
    while (cin >> num) {
        nums2.push_back(num);
        if (cin.peek() == '\n') break; // 遇到換行則停止
    }
    
    Solution solution;
    cout << solution.minAbsoluteSumDiff(nums1, nums2) << endl;

    return 0;
}
