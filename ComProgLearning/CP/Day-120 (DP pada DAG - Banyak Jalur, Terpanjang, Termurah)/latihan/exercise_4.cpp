#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 4: Rekonstruksi Rute Terpanjang
 *
 * DAG berbobot. Cetak total bobot jalur 1 -> N terpanjang pada baris pertama,
 * lalu urutan simpul jalurnya pada baris kedua.
 * Jika tidak terjangkau, cetak "IMPOSSIBLE" saja.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 5 6
// 1 2 3
// 1 3 2
// 2 4 4
// 3 4 1
// 3 5 7
// 4 5 2
// Output:
// 9
// 1 2 4 5
// (ada seri dengan 1 3 5; jalur mana pun yang bernilai 9 diterima)
//
// Test Case 2:
// Input:
// 2 1
// 1 2 7
// Output:
// 7
// 1 2
//
// Test Case 3:
// Input:
// 4 2
// 1 2 5
// 3 4 5
// Output:
// IMPOSSIBLE
 */

#include <bits/stdc++.h>
using namespace std;

const int NEG = -1e9;

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

    vector<int> dp(n + 1, NEG);
    dp[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            if (dp[u] != NEG && dp[u] + w > dp[v])
            {
                dp[v] = dp[u] + w;
            }

            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    cout << dp[n];
}