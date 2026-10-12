

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 1: Urutan Kuliah (Kahn Dasar)
 *
 * Ada N mata kuliah bernomor 1..N dan M aturan prasyarat.
 * Aturan "u v" berarti mata kuliah u harus diambil SEBELUM v.
 * Cetak satu urutan pengambilan yang valid (urutan apa pun boleh).
 * Jika tidak ada urutan yang mungkin, cetak IMPOSSIBLE.
 *
 * Batas: 1 <= N <= 2*10^5, 0 <= M <= 2*10^5
 *
// Test Case 1:
// Input:
// 6 5
// 1 3
// 2 4
// 2 6
// 3 5
// 4 5
// Output:
// 1 2 3 4 6 5
// (urutan lain yang valid juga diterima)
//
// Test Case 2 (ada siklus):
// Input:
// 3 3
// 1 2
// 2 3
// 3 1
// Output:
// IMPOSSIBLE
//
// Test Case 3 (semua terisolasi, tidak ada prasyarat):
// Input:
// 4 0
// Output:
// 1 2 3 4
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

    vector<int> urut;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        urut.push_back(u);

        for (int v : adj[u])
        {
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if ((int)urut.size() < n)
    {
        cout << "ADA SIKLUS\n";
        return 0;
    }

    for (int i = 0; i < n; i++)
        cout << urut[i] << (i + 1 < n ? ' ' : '\n');
}