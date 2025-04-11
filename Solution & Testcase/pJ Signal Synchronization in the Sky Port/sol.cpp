#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std;

int _gcd(int a, int b) {while ((a %= b) && (b %= a)); return a + b;}

void arr_gcd(int &k1, vector<int> &a1, int &k2, vector<int> &a2) {
    if (k1 < k2) {
        swap(k1, k2);
        swap(a1, a2);
    }
    while (k2 > 0) {
        int k = k1 % k2;
        vector<int> tmp(a1.size()), ext(a1.size());
        int hop = k1 / k2;
        for (int i = 0; i < k2; i++) {
            ext[i] = a2[i];
            for (int j = 1; j < hop; j++)
            ext[i] ^= a2[(i + j * k2) % a1.size()];
        }
        for (int i = k2; i < a1.size(); i++)
            ext[i] = ext[i - k2] ^ a2[i - k2] ^ a2[(i + k2 * (hop - 1)) % a1.size()];
        for (int i = 0; i < a1.size(); i++)
            tmp[i] = a1[i] ^ ext[(i + k) % a1.size()];
        k1 = k2, a1 = a2, k2 = k, a2 = tmp;
    }
}

int main() {
    IOS;
    int n, k1, k2, mmax = 0;
    cin >> n >> k1 >> k2;
    vector<int> a1(n), a2(n), ans(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a1[i];
    for (int i = 0; i < n; i++)
        cin >> a2[i];
    arr_gcd(k1, a1, k2, a2);
    mmax = *max_element(a1.begin(), a1.end());
    int d = _gcd(n, k1);
    for (int shift = 0; (1 << shift) <= mmax; shift++) {
        vector<int> filtered(n, 0), tmp(n, 0);
        for (int i = 0; i < n; i++)
            filtered[i] = (a1[i] & (1 << shift)) > 0;

        for (int i = 0; i < d; i++) {
            int prev = i, cur = i + k1;
            while (cur != i) {
                tmp[cur] = tmp[prev] ^ filtered[prev] ^ filtered[(prev + 1) % n];
                prev = cur, cur = (cur + k1) % n;
            }
        }

        int bit = 0;
        for (int i = 0; i < k1; i++)
            bit ^= tmp[i];

        if (bit != filtered[0]) { // Violation. Adjust one bit.
            int cur = d;
            tmp[0] = 1;
            while (cur != 0) {
                tmp[cur] ^= 1;
                cur = (cur + d) % n;
            }
        }

        for (int i = 0; i < n; i++)
            ans[i] ^= (tmp[i] << shift);
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << (i == n - 1 ? "\n" : " ");

    return 0;
}