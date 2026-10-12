/*
============================================================
📋 TUGAS 06: Termurah + Berapa Banyak yang Termurah
============================================================
Source: Varian CSES 1202 (Investigation) untuk DAG
Difficulty: Medium
Topics: min + count bersamaan

PROBLEM:
DAG berbobot non-negatif. Cetak dua bilangan: biaya minimum dari 1 ke N, dan
ADA BERAPA jalur yang mencapai biaya minimum itu (modulo 10^9+7).
Cetak "-1 0" jika tidak terjangkau.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v w

OUTPUT FORMAT:
- dua bilangan pada satu baris

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 4                    5 2
1 2 2
1 3 2
2 4 3
3 4 3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 2                    3 1
1 2 1
2 3 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    -1 0
1 2 1
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

    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> dp_cnt(n + 1, 0);
    vector<int> dp_min(n + 1, MAX);

    dp_cnt[1] = 1;
    dp_min[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            dp_cnt[v] = dp_cnt[v] + dp_cnt[u];
            if (dp_min[u] != MAX)
            {
                dp_min[v] = min(dp_min[u] + w, dp_min[v]);
            }
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    cout << dp_min[n] << " " << dp_cnt[n];
}
