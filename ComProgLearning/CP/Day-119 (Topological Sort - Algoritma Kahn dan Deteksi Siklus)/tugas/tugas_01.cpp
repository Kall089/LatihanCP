/*
============================================================
📋 TUGAS 01: Course Schedule (Bisa Lulus?)
============================================================
Source: LC 207 / CSES 1679 (varian)
Difficulty: Easy
Topics: Kahn, deteksi siklus

PROBLEM:
Ada N mata kuliah dan M pasangan prasyarat. Tentukan apakah semua mata kuliah
bisa diselesaikan.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v  (u harus sebelum v)

OUTPUT FORMAT:
- "YA" atau "TIDAK"

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
2 1                    YA
1 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 2                    TIDAK
1 2
2 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
5 4                    YA
1 2
1 3
2 4
3 4
============================================================
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

    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push(i);
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
        cout << "TIDAK";
    }
    else
    {
        cout << "YA";
    }
}