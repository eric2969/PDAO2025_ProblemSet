#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
template<class T> bool chmin(T &a, T b) { return b < a && (a = b, true); }
template<class T> bool chmax(T &a, T b) { return a < b && (a = b, true); }
typedef long long ll;
const int MAXn = 100000;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll h[MAXn + 5];
ll diff[MAXn + 5];
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        diff[i] = h[i] - h[i - 1];
    }

    while (q--){
        int cmd; cin >> cmd;
        if (cmd <= 2){
            ll l, r, v; cin >> l >> r >> v;
            v *= (cmd == 2 ? -1 : 1);
            diff[l + 1] += v;
            diff[r + 2] -= v;
        }
        else {
            ll len, p1, p2;
            cin >> len >> p1 >> p2;

            for (int i = 1; i <= n; i++)
                h[i] = h[i - 1] + diff[i];

            deque<pair<ll, int>> dq;
            ll s = 0;
            auto Push = [&](int i){
                while (!dq.empty() && dq.back().X <= h[i]) dq.pop_back();
                dq.push_back(make_pair(h[i], i));
            };

            ll cur_s = 0;
            for (int i = 1; i <= len; i++) {
                Push(i);
                cur_s += h[i];
            }
            ll ans = -INF;
            int l = 0;
            for (int i = 1; i + len - 1 <= n; i++){
                if (chmax(ans, 1ll * dq.front().X * p1 + 1ll * cur_s * p2))
                    l = i;

                // transit
                if (i + len <= n) {
                    cur_s -= h[i];
                    cur_s += h[i + len];
                    if (dq.front().Y == i) dq.pop_front();
                    Push(i + len);
                }
            }

            if (ans > 0) cout << l-1 << ' ' << l + len - 2 << ' ' << ans << '\n';
            else cout << "Oiiaioiiiai\n";
        }
    }
    return 0;
}