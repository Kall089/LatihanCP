#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 2: Jalur Terpanjang di DAG
 *
 * DAG berbobot N simpul, M edge "u v w". Cari total bobot terbesar dari
 * jalur 1 -> N. Cetak -1 jika N tidak terjangkau dari 1.
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
// (1-2-4-5 = 3+4+2 = 9, sama dengan 1-3-5 = 2+7 = 9)
//
// Test Case 2 (tidak terjangkau):
// Input:
// 3 1
// 1 2 5
// Output:
// -1
//
// Test Case 3 (rantai lurus, bobot besar):
// Input:
// 4 3
// 1 2 1000000000
// 2 3 1000000000
// 3 4 1000000000
// Output:
// 3000000000
 */

#include <bits/stdc++.h>
using namespace std;

const long long MIN = -1e9;

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

    vector<long long> dp(n + 1, MIN);

    dp[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            if (dp[u] != MIN)
            {
                dp[v] = max(dp[u] + w, dp[v]);
            }

            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (dp[n] != MIN)
    {
        cout << dp[n];
    }
    else
    {
        cout << -1;
    }
}