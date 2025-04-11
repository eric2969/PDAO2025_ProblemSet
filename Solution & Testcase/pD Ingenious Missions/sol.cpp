#include <bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    IOS;
    // Input
    int n, r, m;
    cin >> n >> r >> m;
    vector<int> g(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> g[i] >> b[i];
    }

    // dp part
    vector<vector<vector<int>>> dp(g.size() + 1, vector<vector<int>>(n + 1, vector<int>(r + 1)));
    dp[0][0][0] = 1; // Trivial case where benefit of 0 is satisfied without executing missions

    for (int i = 1; i <= g.size(); i++) { // From 1st mission to the last mission
        int gr = g[i - 1], p = b[i - 1];
        for (int j = 0; j <= n; j++) { // From 0 agents to n agents
            for (int k = 0; k <= r; k++) { // From 0 benefit to r benefit
                dp[i][j][k] = dp[i - 1][j][k]; // Not include this mission
                if (j >= gr) { // If there are enough agents, update dp
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - gr][max(0, k - p)]) % MOD;
                }
            }
        }
    }

    // Get final answers
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        // Updated upwards, use g.size() so all missions are checked
        // 0 agents to n agents, sum up how many schemes generate at least r benefit
        sum = (sum + dp[g.size()][i][r]) % MOD;
    }

    cout << sum;
    return 0;
}