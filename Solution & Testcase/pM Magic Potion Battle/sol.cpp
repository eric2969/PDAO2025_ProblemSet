#include <iostream>
#include <vector>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
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
    IOS;
    int n;
    cin >> n;
    vector<int> potions(n);
    for (int i = 0; i < n; i++) {
        cin >> potions[i];
    }
    
    cout << (magicPotionBattle(potions) ? "Yes" : "No") << endl;
    return 0;
}
