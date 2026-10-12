#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 3: Jalur Termurah di DAG (Bobot Boleh Negatif)
 *
 * DAG berbobot, bobot BOLEH NEGATIF. Cari total bobot terkecil dari jalur
 * 1 -> N. Cetak "TIDAK TERJANGKAU" jika tidak ada jalur.
 * Catatan: Dijkstra TIDAK boleh dipakai di sini.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, -10^9 <= w <= 10^9
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
// 5
// (1-3-4-5 = 2+1+2 = 5)
//
// Test Case 2 (bobot negatif menjebak Dijkstra):
// Input:
// 4 4
// 1 2 1
// 1 3 10
// 2 4 10
// 3 4 -20
// Output:
// -10
// (1-3-4 = 10 + (-20) = -10; Dijkstra akan menjawab 11)
//
// Test Case 3 (tidak terjangkau):
// Input:
// 3 1
// 2 3 5
// Output:
// TIDAK TERJANGKAU
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e18;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});

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

    vector<long long> dp(n + 1, MAX);

    dp[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {

            if (dp[u] != MAX)
            {
                dp[v] = min(dp[v], dp[u] + w);
            }

            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (dp[n] != MAX)
    {
        cout << dp[n];
    }
    else
    {
        cout << "TIDAK TERJANGKAU";
    }
}