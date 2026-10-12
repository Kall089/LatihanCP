/*
============================================================
📋 TUGAS 01: Game Routes
============================================================
Source: CSES 1681
Difficulty: Easy
Topics: banyak jalur di DAG, modulo

PROBLEM:
Sebuah permainan punya N level dan M transisi berarah. Hitung ada berapa cara
menyelesaikan permainan dari level 1 ke level N. Cetak modulo 10^9+7.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, graf DAG

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 5                    3
1 2
2 4
1 3
3 4
1 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 1                    0
1 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1                    1
1 2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

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

    for (int u = 1; u <= n; u++)
    {
        if (indeg[u] == 0)
        {
            q.push(u);
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
            dp[v] = (dp[u] + dp[v]) % MOD;
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    cout << dp[n];
}