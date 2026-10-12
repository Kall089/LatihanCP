/*
============================================================
📋 TUGAS 05: Jalur Termurah dengan Bobot Negatif
============================================================
Source: Latihan sintesis
Difficulty: Medium
Topics: DP min di DAG, jebakan Dijkstra

PROBLEM:
DAG berbobot, bobot boleh negatif. Cari biaya terkecil dari 1 ke N.
Cetak "TIDAK TERJANGKAU" jika tidak ada jalur.
Kerjakan juga versi Dijkstra-nya dan bandingkan hasilnya pada Sampel 2 --
kamu harus bisa menunjukkan Dijkstra memberi jawaban yang salah.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan atau TIDAK TERJANGKAU

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, |w| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    2
1 2 5
2 3 -3
1 3 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4                    -10
1 2 1
1 3 10
2 4 10
3 4 -20

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    TIDAK TERJANGKAU
2 3 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e9;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
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

    vector<int> dp(n + 1, MAX);
    dp[1] = 0;

    int keluar = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            keluar++;
            if (dp[u] != MAX)
            {
                dp[v] = min(dp[u] + w, dp[v]);
            }
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (keluar < n)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        cout << dp[n];
    }
}