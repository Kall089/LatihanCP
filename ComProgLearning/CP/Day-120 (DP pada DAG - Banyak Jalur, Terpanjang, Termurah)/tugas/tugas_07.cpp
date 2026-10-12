/*
============================================================
📋 TUGAS 07: Jalur Terpanjang dari Banyak Sumber
============================================================
Source: Varian klasik (super-source)
Difficulty: Medium
Topics: super-source

PROBLEM:
DAG berbobot. Ada K simpul yang boleh dijadikan titik awal. Cari jalur
terpanjang yang berawal di salah satu dari K simpul itu dan berakhir di N.
Cetak -1 jika tidak ada.

INPUT FORMAT:
- Baris 1: N M K
- Baris 2: K nomor simpul awal
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= K <= N

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 3 2                  9
1 2
1 3 4
2 3 5
3 4 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 3 1                  8
2
1 3 4
2 3 5
3 4 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1 1                  -1
3
1 2 5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
const int NEG = -1e9;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    vector<int> start(k);

    for (int i = 0; i < k; i++)
    {
        cin >> start[i];

        adj[0].push_back({start[i], 0});
        indeg[start[i]]++;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        indeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> dp(n + 1, NEG);

    dp[0] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            if (dp[u] != NEG)
            {
                dp[v] = max(dp[u] + w, dp[v]);
            }

            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (dp[n] == NEG)
    {
        cout << -1;
    }
    else
    {
        cout << dp[n];
    }