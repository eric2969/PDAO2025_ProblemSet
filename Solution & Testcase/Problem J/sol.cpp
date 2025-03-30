#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union for Kruskal's Algorithm
class UnionFind {
public:
    vector<int> group;
    vector<int> rank;

    UnionFind(int size) {
        group.resize(size, 0);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            group[i] = i;
        }
    }

    int find(int node) {
        if (group[node] != node) {
            group[node] = find(group[node]);
        }
        return group[node];
    }

    bool join(int node1, int node2) {
        int group1 = find(node1), group2 = find(node2);

        if (group1 == group2) return false;

        if (rank[group1] > rank[group2]) group[group2] = group1;
        else if (rank[group1] < rank[group2]) group[group1] = group2;
        else {
            group[group1] = group2;
            rank[group2] += 1;
        }
        return true;
    }
};

int findMST(int n, vector<vector<int>>& edges, int incl, int excl);

int main() {
    // Input
    int n = 0, m = 0;
    cin >> n >> m;

    // Read edges as (node1, node2, weight, index)
    vector<vector<int>> indexedEdges(m, vector<int>(4));
    for (int i = 0; i < m; i++) {
        cin >> indexedEdges[i][0] >> indexedEdges[i][1] >> indexedEdges[i][2];
        indexedEdges[i][3] = i;
    }

    // Sort edges by weight
    sort(indexedEdges.begin(), indexedEdges.end(), [](const auto& e1, const auto& e2) {
        return e1[2] < e2[2];
    });

    // Find the weight without restrictions
    int mstWeight = findMST(n, indexedEdges, -1, -1);

    // Find the weight with each edges included or excluded.
    vector<int> critical, pseudoCritical;
    for (int i = 0; i < m; i++) {
        int originalIndex = indexedEdges[i][3];

        // Including case
        int inclWeight = findMST(n, indexedEdges, i, -1);

        // Excluding case
        int exclWeight = findMST(n, indexedEdges, -1, i);

        if (exclWeight > mstWeight) {
            critical.push_back(originalIndex);
        } else if (inclWeight == mstWeight) {
            pseudoCritical.push_back(originalIndex);
        }
    }

    // Output
    if (critical.empty()) {
        cout << "no channels\n";
    } else {
        for (size_t i = 0; i < critical.size(); i++) {
            if (i > 0) cout << " ";
            cout << critical[i];
        }
        cout << "\n";  // Use explicit \n instead of endl
    }

    if (pseudoCritical.empty()) {
        cout << "no channels\n";
    } else {
        for (size_t i = 0; i < pseudoCritical.size(); i++) {
            if (i > 0) cout << " ";
            cout << pseudoCritical[i];
        }
        cout << "\n";  // Use explicit \n instead of endl
    }
    return 0;
}

int findMST(int n, vector<vector<int>>& edges, int incl, int excl) {
    UnionFind uf(n);
    int weight = 0;
    
    // If we need to force an edge, add it first
    if (incl != -1) {
        weight += edges[incl][2];
        uf.join(edges[incl][0], edges[incl][1]);
    }
    
    // Add remaining edges if they form valid connections. (Kruskal's Algorithm)
    for (int i = 0; i < edges.size(); i++) {
        if (i == incl || i == excl) continue;
        
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        if (uf.join(u, v)) {
            weight += w;
        }
    }
    
    // Check if we have a valid MST
    int root = uf.find(0);
    for (int i = 1; i < n; i++) {
        if (uf.find(i) != root) return INT_MAX;
    }
    
    return weight;
}
