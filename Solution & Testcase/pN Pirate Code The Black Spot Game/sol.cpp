#include <iostream>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std;

int findTheWinner(int n, int k) {
    int s = 0;
    for(int i = 2; i <= n; i++) s = (s+k) % i;
    return s;
}


int main() {
    IOS;
    int n, k;
    int people, mod;
    cin >> n >> k;
    int result = findTheWinner(n, k);
    for(int i = 0;i <= result;i++)
        cin >> people >> mod;
    cout << result << ' ' << findTheWinner(people, mod) << endl;
    return 0;
}