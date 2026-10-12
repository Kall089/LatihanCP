#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 3: Urutan Topologis Leksikografis Terkecil
 *
 * Sama seperti Latihan 1, tetapi jika ada beberapa urutan yang valid,
 * cetak yang paling kecil secara leksikografis (bandingkan sebagai barisan
 * angka: 1 3 2 lebih kecil daripada 2 1 3).
 * Cetak IMPOSSIBLE jika tidak ada.
 *
 * Batas: 1 <= N, M <= 2*10^5
 *
// Test Case 1:
// Input:
// 5 4
// 1 4
// 2 4
// 3 5
// 4 5
// Output:
// 1 2 3 4 5
//
// Test Case 2:
// Input:
// 4 2
// 4 1
// 3 2
// Output:
// 3 2 4 1
//
// Test Case 3 (siklus):
// Input:
// 3 3
// 2 1
// 1 3
// 3 2
// Output:
// IMPOSSIBLE
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

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> urut;

    while (!q.empty())
    {
        int u = q.top();
        q.pop();

        urut.push_back(u);

        for (int v : adj[u])
        {
            if (--indeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (urut.size() < n)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        for (int i = 0; i < urut.size(); i++)
        {
            cout << urut[i] << " ";
        }
    }
}