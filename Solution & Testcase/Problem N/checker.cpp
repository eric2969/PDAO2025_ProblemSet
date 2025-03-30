#include <vector>
#include <fstream>
using namespace std;

// 計算從 start 出發，連續 k 個數的 XOR（環狀計算）
int cyclicXor(const vector<int>& seq, int start, int k, int N) {
    int res = 0;
    for (int i = 0; i < k; i++)
        res ^= seq[(start + i) % N];
    return res;
}

int main(int argc, char* argv[]) {
    ifstream testInput, studentInput;
    int N, k1, k2;

    testInput.open(argv[1]);
    studentInput.open(argv[2]);

    // 讀取測資中的 N, k1, k2
    testInput >> N >> k1 >> k2;
    // 讀取 a 與 b 數列
    vector<int> a(N), b(N), candidate(N);
    for (int i = 0; i < N; i++)
        testInput >> a[i];
    for (int i = 0; i < N; i++)
        testInput >> b[i];
    // 讀取參賽者候選解，並確保其為非負整數
    for (int i = 0; i < N; i++){
        studentInput >> candidate[i];
        if (candidate[i] < 0 || candidate[i] > (1 << 30) - 1)
            return 0;
    }
    // 檢查地0個起始位置的 XOR 值是否符合要求
    int xor_k1 = cyclicXor(candidate, 0, k1, N);
    int xor_k2 = cyclicXor(candidate, 0, k2, N);
    if (xor_k1 != a[0] || xor_k2 != b[0]) return 0;
    // 檢查每個起始位置的 XOR 值是否符合要求
    for (int i = 1; i < N; i++) {
        xor_k1 ^= (candidate[(i + k1 - 1)%N] ^ candidate[(i + N - 1)%N]);
        xor_k2 ^= (candidate[(i + k2 - 1)%N] ^ candidate[(i + N - 1)%N]);
        if (xor_k1 != a[i] || xor_k2 != b[i])
            return 0;
    }
    // 所有檢查通過，回報 AC
    return 1;
}
