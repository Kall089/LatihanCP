/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_2.cpp
 * Topik : Connected Components — Hitung & Ukuran Terbesar
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge. Graph TIDAK dijamin
 * terhubung. Cetak dua nilai:
 *   1. Banyaknya connected component (kelompok node yang saling terhubung)
 *   2. Ukuran (jumlah node) dari komponen TERBESAR
 *
 * Idea:
 *   Loop semua node 1..N. Setiap kali menemukan node yang belum dikunjungi,
 *   itu adalah awal komponen BARU — tambah counter, lalu DFS dari sana.
 *   DFS akan menandai seluruh node di komponen itu sekaligus.
 *
 *   for (int i = 1; i <= n; i++)
 *       if (!visited[i]) { components++; size = dfs(i); }
 *
 * Agar bisa menghitung ukuran, buat dfs mengembalikan jumlah node yang
 * ditandainya (atau pakai variabel counter global).
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : Dua bilangan dipisah spasi — jumlah komponen, ukuran terbesar
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 6 3                    3 3
 * 1 2
 * 2 3
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 4 0                    4 1
 *
 * Sample Input 3:        Sample Output 3:
 * 5 4                    1 5
 * 1 2
 * 2 3
 * 3 4
 * 4 5
 *
 * NOTE Sample 1: komponen {1,2,3} (ukuran 3), {4,5} (ukuran 2), {6} (ukuran 1)
 *                → 3 komponen, terbesar = 3.
 * NOTE Sample 2: tidak ada edge → tiap node komponen sendiri → 4 komponen,
 *                masing-masing ukuran 1.
 *
 * HINT: Jangan lupa node yang terisolasi (tanpa edge sama sekali) tetap
 *       dihitung sebagai satu komponen.
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited, int &j)
{
    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            j++;
            dfs(v, adj, visited, j);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);

    while (m--)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int max_val = 0;
    int j;
    int komponen = 0;

    for (int i = 1; i <= n; i++)
    {
        j = 1;
        if (!visited[i])
        {
            komponen++;
            dfs(i, adj, visited, j);
            max_val = max(max_val, j);
        }
    }
    cout << komponen << " " << max_val;
}
