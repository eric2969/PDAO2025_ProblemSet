#include <bits/stdc++.h>
using namespace std;

struct UnionSet {
  int n;
  vector<int> sz, pa;
  UnionSet() {}
  UnionSet(int n_): n(n_) {
    sz.resize(n, 1);
    pa.resize(n);
    iota(pa.begin(), pa.end(), 0);
  }

  int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    sz[y] += sz[x], pa[x] = y;
    return true;
  }
};

void Solve() {
  // O(MlogM)
  int N, M; cin >> N >> M;
  vector<array<int, 4>> edges(M);
  for (int i = 0; i < M; i++) {
    int u, v, w; cin >> u >> v >> w;
    edges[i] = {w, u, v, i};
  }
  sort(edges.begin(), edges.end());

  // -1: backup, 0: non, 1: critical
  vector<int> edges_type(M, -1);
  UnionSet dsu(N);

  vector<int> vis(M), tin(N);
  int dfs_clock = 0;
  vector<vector<pair<int, int>>> g(N, vector<pair<int, int>>());
  auto Dfs = [&](auto self, int u) -> int {
    int lowu = tin[u] = ++dfs_clock;
    for (auto& iter : g[u]) {
      int v = iter.first, idx = iter.second;
      if (vis[idx]++) continue;
      if (tin[v])
        lowu = min(lowu, tin[v]);
      else {
        int lowv = self(self, v);
        lowu = min(lowu, lowv);
        if (lowv > tin[u]) edges_type[idx] = 1;
      }
    }
    return lowu;
  };

  auto Process = [&](int l, int r) {
    for (int i = l; i < r; i++) {
      int w = edges[i][0], u = edges[i][1], v = edges[i][2], idx = edges[i][3];
      u = dsu.find(u), v = dsu.find(v);
      if (u == v) edges_type[idx] = 0;
      else {
        g[u].emplace_back(v, idx);
        g[v].emplace_back(u, idx);
      }
    }
    for (int i = l; i < r; i++) {
      int w = edges[i][0], u = edges[i][1], v = edges[i][2], idx = edges[i][3];
      if (!vis[idx]) Dfs(Dfs, dsu.find(u));
    }

    dfs_clock = 0;
    for (int i = l; i < r; i++) {
      int w = edges[i][0], u = edges[i][1], v = edges[i][2], idx = edges[i][3];
      u = dsu.find(u), v = dsu.find(v);
      tin[u] = tin[v] = 0;
      g[u].clear(), g[v].clear();
      dsu.merge(u, v);
    }
  };
  for (int i = 0, j = 0; i < M; i = j) {
    while (j < M && edges[i][0] == edges[j][0])
      j++;
    Process(i, j);
  }
  vector<int> edges_critical, edges_backup;
  for (int i = 0; i < M; i++) {
    if (edges_type[i] == -1) edges_backup.push_back(i);
    else if (edges_type[i] == 1) edges_critical.push_back(i);
  }
  auto Print = [&](const vector<int> &v) -> void {
    if (v.empty()) cout << "no channels\n";
    else {
      for (int i = 0; i < v.size(); i++)
        cout << (i ? " " : "") << v[i];
      cout << '\n';
    }
  };
  Print(edges_critical);
  Print(edges_backup);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  Solve();
  return 0;
}