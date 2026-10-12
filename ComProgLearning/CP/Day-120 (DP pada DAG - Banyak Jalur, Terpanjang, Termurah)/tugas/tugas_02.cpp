/*
============================================================
📋 TUGAS 02: Longest Path (AtCoder DP-G)
============================================================
Source: AtCoder Educational DP Contest G
Difficulty: Easy
Topics: jalur terpanjang di DAG (tanpa bobot)

PROBLEM:
DAG dengan N simpul dan M edge. Cari panjang (banyak EDGE) jalur terpanjang
di seluruh graf -- boleh mulai dan berakhir di simpul mana pun.

INPUT FORMAT:
- Baris 1: N M
- M baris: x y

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 2 <= N <= 10^5, 1 <= M <= 10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 5                    3
1 2
1 3
3 2
2 4
3 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
6 3                    2
2 3
4 5
5 6

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1                    1
1 2
============================================================
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

    for (int u = 1; u <= n; u++)
    {
        if (indeg[u] == 0)
        {
            q.push(u);
        }
    }

    vector<int> dp(n + 1, 0);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {

            dp[v] = max(dp[u] + 1, dp[v]);

            if (--indeg[v] == 0)
            {

                q.push(v);
            }
        }
    }

    cout << dp[n];
}
