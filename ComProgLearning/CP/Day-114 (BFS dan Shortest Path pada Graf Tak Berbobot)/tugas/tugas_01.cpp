/*
============================================================
📋 TUGAS 01: Hitung Jumlah Node yang Dapat Dijangkau
============================================================
Source: Original
Difficulty: Easy
Topics: BFS dasar, visited array, connected component

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge. Diberikan node sumber S.
Hitung berapa banyak node yang dapat dijangkau dari S
(termasuk S sendiri).

INPUT FORMAT:
- Baris 1: tiga integer n, m, S
- m baris berikutnya: dua integer u v (edge undirected)

OUTPUT FORMAT:
- Satu baris: integer (jumlah node yang dapat dijangkau dari S)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- 1 ≤ S ≤ n

SAMPLE INPUT 1:
5 4 1
1 2
1 3
2 4
4 5

SAMPLE OUTPUT 1:
5

SAMPLE INPUT 2:
6 3 1
1 2
1 3
4 5

SAMPLE OUTPUT 2:
3

NOTE: Node 4, 5, 6 tidak terjangkau dari node 1.
      Dari node 1 hanya bisa ke 1, 2, 3 → jawaban 3.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;

    q.push(s);
    dist[s] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (dist[v] != -1)
            {
                continue;
            }

            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    int jumlah = 0;

    for (int j = 1; j <= n; j++)
    {
        if (dist[j] != -1)
        {
            jumlah++;
        }
    }

    cout << jumlah;
}