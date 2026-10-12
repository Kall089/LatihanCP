#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 1: Banyak Jalur dari 1 ke N
 *
 * DAG berarah N simpul, M edge tak berbobot. Hitung ada berapa jalur berbeda
 * dari simpul 1 ke simpul N. Cetak hasilnya modulo 10^9+7.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, graf dijamin DAG
 *
// Test Case 1:
// Input:
// 5 6
// 1 2
// 1 3
// 2 4
// 3 4
// 3 5
// 4 5
// Output:
// 3
// (1-2-4-5, 1-3-4-5, 1-3-5)
//
// Test Case 2 (tidak terjangkau):
// Input:
// 4 2
// 1 2
// 3 4
// Output:
// 0
//
// Test Case 3 (bercabang lebar):
// Input:
// 6 8
// 1 2
// 1 3
// 2 4
// 2 5
// 3 4
// 3 5
// 4 6
// 5 6
// Output:
// 4
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

    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            dp[v] = dp[v] + dp[u];
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    cout << dp[n];
}