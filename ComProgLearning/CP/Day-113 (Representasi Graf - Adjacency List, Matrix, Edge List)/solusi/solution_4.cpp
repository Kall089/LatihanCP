/*
============================================================
  Solution 4: Adjacency Matrix Operations
============================================================
Kompleksitas: O(n³) untuk transitive closure dan matrix multiplication.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mat[i][j];

    // In-degree & Out-degree
    cout << "=== In-degree / Out-degree ===\n";
    vector<int> in_d(n + 1, 0), out_d(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j]) { out_d[i]++; in_d[j]++; }

    for (int u = 1; u <= n; u++) {
        cout << "Node " << u << ": in=" << in_d[u] << ", out=" << out_d[u];
        if (in_d[u] == 0) cout << "  [SOURCE]";
        if (out_d[u] == 0) cout << "  [SINK]";
        cout << "\n";
    }

    // Transitive Closure (Floyd-Warshall)
    cout << "\n=== Transitive Closure ===\n";
    vector<vector<int>> reach(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            reach[i][j] = (mat[i][j] > 0) ? 1 : 0;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                reach[i][j] |= (reach[i][k] & reach[k][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << reach[i][j] << (j < n ? " " : "\n");
    }

    // Path length exactly 2 (matrix multiplication)
    cout << "\n=== Path panjang tepat 2 ===\n";
    vector<vector<int>> mat2(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                mat2[i][j] += mat[i][k] * mat[k][j];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << mat2[i][j] << (j < n ? " " : "\n");
    }
    return 0;
}
