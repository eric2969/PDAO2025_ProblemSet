#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream studentInput, testcase;
    
    testcase.open(argv[1]);
    studentInput.open(argv[2]);

    int m, n;
    testcase >> m >> n;

    vector<vector<int>> inputGrid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            testcase >> inputGrid[i][j];
        }
    }

    vector<vector<int>> outputGrid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            studentInput >> outputGrid[i][j];
        }
    }

    // Check that rows and columns maintain order
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (inputGrid[i][j - 1] < inputGrid[i][j] && outputGrid[i][j - 1] >= outputGrid[i][j]) {
                return 0;
            }
        }
    }
    
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < m; i++) {
            if (inputGrid[i - 1][j] < inputGrid[i][j] && outputGrid[i - 1][j] >= outputGrid[i][j]) {
                return 0;
            }
        }
    }
    
    return 1;
}