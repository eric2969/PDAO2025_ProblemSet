#include <iostream>
using namespace std;

class Solution {
public:
    int findTheWinner(int n, int k) {
        int s = 0; //一開始的編號
        for(int i = 2; i <= n; i++) s = (s+k) % i; //第 i 輪中，他的位置是第 s 
        return s; //如果題目的編號一開始是 1，那我們就加一
    }
};


int main() {
    Solution sol;
    int n = 0, k = 0;
    int people[1000], mod[1000];
    cin >> n >> k;
    for(int i = 0;i < n;i++)
        cin >> people[i] >> mod[i];
    int result = sol.findTheWinner(n, k);
    cout << result << ' ' << sol.findTheWinner(people[result], mod[result]) << endl;
    return 0;
}