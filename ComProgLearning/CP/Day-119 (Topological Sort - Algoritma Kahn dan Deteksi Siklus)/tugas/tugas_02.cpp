/*
============================================================
📋 TUGAS 02: Course Schedule II (Cetak Urutannya)
============================================================
Source: LC 210
Difficulty: Easy
Topics: Kahn

PROBLEM:
Sama seperti Tugas 01, tetapi cetak SATU urutan valid. Jika tidak ada,
cetak baris kosong.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v

OUTPUT FORMAT:
- N bilangan dipisah spasi, atau baris kosong

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 4                    1 2 3 4
1 2
1 3
2 4
3 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
1 0                    1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 3                    (baris kosong)
1 2
2 3
3 1
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
        int u = q.front();
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

    for (int i = 0; i < urut.size(); i++)
    {
        cout << urut[i] << " ";
    }
}