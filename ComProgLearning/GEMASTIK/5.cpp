#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<tuple<int, int, int>>> adj(n + 1);
    int awal = 0;

    for (int i = 0; i < n; i++)
    {
        int u, v, w, z;
        adj[u].push_back({v, w, z});
        awal = u;
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        long long T, hitung = 0;
        cin >> T;

        queue<int> que;
        que.push(awal);

        while (!que.empty())
        {
            int u = que.front();
            que.pop();

            for (auto [v, w, z] : adj[u])
            {
                hitung += w;
                que.push(v);
            }
        }
    }
}