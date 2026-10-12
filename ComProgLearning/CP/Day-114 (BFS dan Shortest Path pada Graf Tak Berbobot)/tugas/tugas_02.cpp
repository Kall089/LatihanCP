/*
============================================================
📋 TUGAS 02: Jarak Terpendek dari Satu Sumber
============================================================
Source: Original
Difficulty: Easy
Topics: BFS, shortest path, unweighted graph

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge. Diberikan sumber S dan q buah query.
Untuk setiap query berikan sebuah node T, jawab berapa
jarak terpendek dari S ke T. Jika tidak ada jalur, cetak -1.

INPUT FORMAT:
- Baris 1: tiga integer n, m, S
- m baris berikutnya: dua integer u v
- Baris berikutnya: integer q
- q baris berikutnya: integer T

OUTPUT FORMAT:
- q baris, masing-masing satu integer (jarak atau -1)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- 1 ≤ q ≤ 10^5

SAMPLE INPUT 1:
5 5 1
1 2
2 3
3 4
4 5
1 5
3
3
5
4

SAMPLE OUTPUT 1:
2
1
3

SAMPLE INPUT 2:
4 2 1
1 2
3 4
2
2
3

SAMPLE OUTPUT 2:
1
-1

NOTE: Jalankan BFS dari S sekali saja (O(V+E)),
      simpan semua dist[], lalu jawab setiap query O(1).
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
    }

    for (int i = 0; i < n; i++)
    {
        cout << i << ": ";
        for (int t : adj[i])
        {
            cout << t << " ";
        }
        cout << endl;
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

    cout << "=== Jarak dari node " << s << " ===\n";
    for (int u = 1; u <= n; u++)
        cout << "dist(" << u << ") = " << dist[u] << "\n";

    int qq;
    cin >> qq;

    while (qq--)
    {
        int t;
        cin >> t;
        cout << dist[t] << "\n";
    }
}