#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 5: Berapa Semester Minimum?
 *
 * N mata kuliah, M prasyarat "u v" (u sebelum v). Dalam satu semester kamu
 * boleh mengambil BERAPA PUN mata kuliah, asalkan semua prasyaratnya sudah
 * selesai di semester-semester sebelumnya.
 * Cetak jumlah semester minimum. Jika mustahil, cetak -1.
 *
 * Batas: 1 <= N, M <= 2*10^5
 *
// Test Case 1:
// Input:
// 6 5
// 1 3
// 2 4
// 2 6
// 3 5
// 4 5
// Output:
// 3
// (sem1: 1,2   sem2: 3,4,6   sem3: 5)
//
// Test Case 2 (rantai lurus):
// Input:
// 5 4
// 1 2
// 2 3
// 3 4
// 4 5
// Output:
// 5
//
// Test Case 3 (siklus):
// Input:
// 2 2
// 1 2
// 2 1
// Output:
// -1
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
}