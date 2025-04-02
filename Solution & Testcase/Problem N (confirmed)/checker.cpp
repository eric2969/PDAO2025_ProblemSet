#include <vector>
#include <fstream>
using namespace std;

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

    testInput >> N >> k1 >> k2;

    vector<int> a(N), b(N), candidate(N);
    for (int i = 0; i < N; i++)
        testInput >> a[i];
    for (int i = 0; i < N; i++)
        testInput >> b[i];

    for (int i = 0; i < N; i++){
        studentInput >> candidate[i];
        if (candidate[i] < 0 || candidate[i] > (1 << 30) - 1)
            return 0;
    }

    int xor_k1 = cyclicXor(candidate, 0, k1, N);
    int xor_k2 = cyclicXor(candidate, 0, k2, N);
    if (xor_k1 != a[0] || xor_k2 != b[0]) return 0;

    for (int i = 1; i < N; i++) {
        xor_k1 ^= (candidate[(i + k1 - 1)%N] ^ candidate[(i + N - 1)%N]);
        xor_k2 ^= (candidate[(i + k2 - 1)%N] ^ candidate[(i + N - 1)%N]);
        if (xor_k1 != a[i] || xor_k2 != b[i])
            return 0;
    }

    return 1;
}
