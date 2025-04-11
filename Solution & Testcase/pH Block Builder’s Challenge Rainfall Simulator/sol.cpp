#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

signed main(int argc, char** argv) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> heightMap(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int temp = 0;
            cin >> temp;
            heightMap[i][j] = temp;
        }
    }
    priority_queue<pair<int, pair<int, int>>, 
    vector<pair<int, pair<int, int>>>, 
    greater<>> boundary;
    
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    int a = heightMap.size();
    int b = heightMap[0].size();
    
    vector<vector<bool>> visited(a, vector<bool>(b, false));
    
    for (int i = 0; i < a; i++) {
        boundary.push({heightMap[i][0], {i, 0}});
        boundary.push({heightMap[i][b-1], {i, b-1}});
        visited[i][0] = true;
        visited[i][b-1] = true;
    }
    
    for (int i = 0; i < b; i++) {
        boundary.push({heightMap[0][i], {0, i}});
        boundary.push({heightMap[a-1][i], {a-1, i}});
        visited[0][i] = true;
        visited[a-1][i] = true;
    }
    
    int ans = 0;
    while (!boundary.empty()) {
        int height = boundary.top().first;
        auto position = boundary.top().second;
        
        auto positionX = position.first;
        auto positionY = position.second;
        boundary.pop();
    
        for (int direction = 0; direction < 4; direction++) {
            int newX = positionX + dirs[direction].first;
            int newY = positionY + dirs[direction].second;
            
            if (newX >= 0 && newX < a && newY >= 0 && newY < b && !visited[newX][newY]) {
                int newHeight = heightMap[newX][newY];
                
                if (newHeight < height)
                    ans += height - newHeight;
                
                boundary.push({max(newHeight, height), {newX, newY}});
                visited[newX][newY] = true;
            }
        }
    }

    cout << ans;
    return 0;
}
