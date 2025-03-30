#include <bits/stdc++.h>
using namespace std;

int main() {
    // Input
    int n = 0, m = 0;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // Store the values of the matrix and their indices.
    vector<tuple<int, int, int>> nums;

    // Store the minimum values for every row and column.
    vector<int> rows(n, 1);
    vector<int> cols(m, 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            nums.push_back(make_tuple(grid[i][j], i, j));
        }
    }
    sort(nums.begin(), nums.end());

    for (auto tup : nums) {
        int val, x, y;
        tie(val, x, y) = tup;
        // Find the maximum value of rows[x] and cols[y] till now and assign it to val.
        val = max(rows[x], cols[y]);
        grid[x][y] = val;
        // Update the new maximum value in rows[x] and cols[y].
        rows[x] = cols[y] = val + 1;
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i][0];
        for (int j = 1; j < m; j++) {
            cout << " " << grid[i][j];
        }
        cout << endl;
    }

    return 0;
}