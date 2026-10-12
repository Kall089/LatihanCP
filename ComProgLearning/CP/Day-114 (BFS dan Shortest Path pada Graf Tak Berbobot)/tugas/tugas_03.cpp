/*
============================================================
📋 TUGAS 03: Node di Level ke-K
============================================================
Source: Original
Difficulty: Easy
Topics: BFS, level traversal, distance

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge, serta sumber S dan bilangan K.
Cetak semua node yang berjarak tepat K dari S, diurutkan
secara ascending. Jika tidak ada, cetak "TIDAK ADA".

INPUT FORMAT:
- Baris 1: empat integer n, m, S, K
- m baris berikutnya: dua integer u v

OUTPUT FORMAT:
- Satu baris: node-node yang berjarak tepat K dari S,
  dipisah spasi, urutan ascending.
  Atau "TIDAK ADA" jika tidak ada.

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- 0 ≤ K ≤ n

SAMPLE INPUT 1:
6 5 1 2
1 2
1 3
2 4
3 5
5 6

SAMPLE OUTPUT 1:
4 5

SAMPLE INPUT 2:
4 3 1 3
1 2
2 3
3 4

SAMPLE OUTPUT 2:
4

NOTE: Jalankan BFS dari S, kumpulkan semua node dengan
      dist[u] == K, urutkan, lalu cetak.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, s, k;
    bool ada = false;
    cin >> n >> m >> s >> k;

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

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == k)
        {
            cout << i << " ";
            ada = true;
        }
    }

    if (!ada)
    {
        cout << "tidak ada";
    }
}