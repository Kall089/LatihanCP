#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 5: Tiga Jawaban dalam Satu Sapuan
 *
 * DAG berbobot. Dalam SATU kali sapuan urutan topologis, hitung sekaligus:
 *   baris 1: banyak jalur 1 -> N  (mod 10^9+7)
 *   baris 2: bobot jalur terpanjang 1 -> N, atau -1
 *   baris 3: bobot jalur termurah 1 -> N, atau -1
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
// 3
// 9
// 5
//
// Test Case 2 (jalur tunggal):
// Input:
// 3 2
// 1 2 4
// 2 3 6
// Output:
// 1
// 10
// 10
//
// Test Case 3 (tidak terjangkau):
// Input:
// 4 2
// 1 2 3
// 3 4 3
// Output:
// 0
// -1
// -1
 */

#include <bits/stdc++.h>
using namespace std;

const int NEG = -1e9;
const int POS = 1e9;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> indeg(n + 1);

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

    vector<int> cnt(n + 1, 0), best(n + 1, NEG), cheap(n + 1, POS);

    cnt[1] = 1, best[1] = 0, cheap[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
        {
            cnt[v] = cnt[u] + cnt[v];

            if (best[u] != NEG)
            {
                best[v] = max(best[u] + w, best[v]);
            }

            if (cheap[u] != POS)
            {
                cheap[v] = min(cheap[u] + w, cheap[v]);
            }

            if (--indeg[v] == 0)
            {

                q.push(v);
            }
        }
    }

    cout << cnt[n] << endl;
    cout << best[n] << endl;
    cout << cheap[n];
}