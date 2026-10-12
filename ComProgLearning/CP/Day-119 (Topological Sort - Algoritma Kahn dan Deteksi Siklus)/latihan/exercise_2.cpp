#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 2: Deteksi Siklus pada Graf Berarah
 *
 * Diberikan graf berarah dengan N simpul dan M edge.
 * Cetak "YA" jika graf memiliki siklus, "TIDAK" jika tidak.
 * Gunakan Kahn — bukan DFS.
 *
 * Batas: 1 <= N, M <= 2*10^5
 *
// Test Case 1:
// Input:
// 4 4
// 1 2
// 2 3
// 3 4
// 4 2
// Output:
// YA
// (siklus 2 -> 3 -> 4 -> 2)
//
// Test Case 2:
// Input:
// 5 4
// 1 2
// 1 3
// 3 4
// 2 5
// Output:
// TIDAK
//
// Test Case 3 (self-loop):
// Input:
// 2 1
// 2 2
// Output:
// YA
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;

    for (int u = 1; u <= n; u++)
    {
        if (indeg[u] == 0)
        {
            q.push(u);
        }
    }

    int keluar = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        keluar++;

        for (int v : adj[u])
        {
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (keluar < n)
    {
        cout << "YA";
    }
    else
    {
        cout << "TIDAK";
    }
}