#include <iostream>
#include <vector>
using namespace std;

bool magicPotionBattle(const vector<int>& potions) {
    int cnt[3] = {};
    for (int essence : potions)
        cnt[essence % 3]++;
    
    if (min(cnt[1], cnt[2]) == 0)
        return max(cnt[1], cnt[2]) > 2 && cnt[0] % 2 > 0;
    return abs(cnt[1] - cnt[2]) > 2 || cnt[0] % 2 == 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> potions(n);
    for (int i = 0; i < n; i++) {
        cin >> potions[i];
    }
    
    cout << (magicPotionBattle(potions) ? "true" : "false") << endl;
    return 0;
}
