#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 20000 + 5;

struct SegmentTree {
    unsigned long long sum[4 * MAXN], max_height[4 * MAXN], lazy[4 * MAXN]; // ������蝮賢�� & ��嗆��閮�

    // **撱箸��蝺�畾菜邦**
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            sum[node] = max_height[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, node * 2, start, mid);
        build(arr, node * 2 + 1, mid + 1, end);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
        max_height[node] = max(max_height[node * 2], max_height[node * 2 + 1]);
    }

    // **銝���冽�嗆��閮�**
    void push_down(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = (start + end) / 2;
            sum[node * 2] += lazy[node] * (mid - start + 1);
            sum[node * 2 + 1] += lazy[node] * (end - mid);
            max_height[node * 2] += lazy[node];
            max_height[node * 2 + 1] += lazy[node];
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    // **���������瘜�嚗���質�伐��**
    void update(int node, int start, int end, int l, int r, int val) {
        if (l > end || r < start) return;

        if (l <= start && end <= r) {
            sum[node] += (end - start + 1) * val;
            max_height[node] += val;
            lazy[node] += val;
            return;
        }

        push_down(node, start, end);
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, val);
        update(node * 2 + 1, mid + 1, end, l, r, val);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
        max_height[node] = max(max_height[node * 2], max_height[node * 2 + 1]);
    }

    // **������皜�瘜�嚗�憭拍�嗥�賢拿皜����嚗�**
    void reduce(int node, int start, int end, int l, int r, int val) {
        if (l > end || r < start) return;

        if (l <= start && end <= r) {
            max_height[node] = max_height[node] - val;
            sum[node] = sum[node] - (end - start + 1) * val;
            lazy[node] -= val;
            return;
        }

        push_down(node, start, end);
        int mid = (start + end) / 2;
        reduce(node * 2, start, mid, l, r, val);
        reduce(node * 2 + 1, mid + 1, end, l, r, val);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
        max_height[node] = max(max_height[node * 2], max_height[node * 2 + 1]);
    }

    // **��������亥岷嚗�蝮賜����瑕漲嚗�**
    int query_sum(int node, int start, int end, int l, int r) {
        if (l > end || r < start) return 0;
        if (l <= start && end <= r) return sum[node];
        push_down(node, start, end);
        int mid = (start + end) / 2;
        return query_sum(node * 2, start, mid, l, r) + query_sum(node * 2 + 1, mid + 1, end, l, r);
    }

    // **��������亥岷嚗����憭折��摨佗��**
    int query_max(int node, int start, int end, int l, int r) {
        if (l > end || r < start) return 0;
        if (l <= start && end <= r) return max_height[node];
        push_down(node, start, end);
        int mid = (start + end) / 2;
        return max(query_max(node * 2, start, mid, l, r), query_max(node * 2 + 1, mid + 1, end, l, r));
    }
};

void query_value(SegmentTree segTree, int N, int LEN, int P1, int P2){
    long long best_price = 0; int best_index = 0;
    for (int L = 1; L <= N - (LEN - 1); L++) {
        long long maxH = segTree.query_max(1, 1, N, L, L + LEN - 1);
        long long totalSum = segTree.query_sum(1, 1, N, L, L + LEN - 1);
        long long price = (maxH * P1) + (totalSum * P2);
        if(price > best_price) {
            best_price = price;
            best_index = L;
        }
    }
    if(best_price == 0)
        cout << "0 0 0\n";
    else
        cout << best_index << " " << best_index+LEN-1 << " " << best_price << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q, P1, P2, LEN;
    cin >> N >> Q;

    vector<int> arr(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    SegmentTree segTree;
    segTree.build(arr, 1, 1, N);

    while (Q--) {
        int type, L, R, val;
        cin >> type;
        if (type == 1) {
            cin >> L >> R >> val;
            segTree.update(1, 1, N, L, R, val);
        } else if (type == 2) {
            cin >> L >> R >> val;
            segTree.reduce(1, 1, N, L, R, val);
        } else if (type == 3) {
            cin >> LEN >> P1 >> P2;
            query_value(segTree, N, LEN, P1, P2);
        }
    }
    return 0;
}
