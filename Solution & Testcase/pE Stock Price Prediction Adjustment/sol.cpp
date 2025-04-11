#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
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
    IOS;
    vector<long long> nums1, nums2;  // 動態大小的 vector
    string line;
    
    // 讀取 nums1
    int n;
    long long num;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> num;
        nums1.push_back(num);
    }
    for(int i = 0; i < n; i++) {
        cin >> num;
        nums2.push_back(num);
    }
    
    Solution solution;
    cout << solution.minAbsoluteSumDiff(nums1, nums2) << endl;

    return 0;
}
