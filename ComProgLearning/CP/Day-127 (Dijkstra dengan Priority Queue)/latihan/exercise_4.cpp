#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 4: Menghitung Banyak Jalur Terpendek
 *
 * Graf BERARAH berbobot POSITIF. Cetak dua bilangan: jarak terpendek 1 -> N,
 * dan ada berapa jalur berbeda yang mencapai jarak itu (modulo 10^9+7).
 * Cetak "-1 0" jika tak terjangkau.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 4 5
// 1 2 1
// 1 3 1
// 2 4 1
// 3 4 1
// 1 4 5
// Output:
// 2 2
//
// Test Case 2 (jalur tunggal):
// Input:
// 3 2
// 1 2 3
// 2 3 4
// Output:
// 7 1
//
// Test Case 3 (tiga cabang seri):
// Input:
// 5 6
// 1 2 2
// 1 3 2
// 1 4 2
// 2 5 3
// 3 5 3
// 4 5 3
// Output:
// 5 3
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // if (baru <  dist[v]) { dist[v] = baru; cnt[v] = cnt[u]; push; }
    // if (baru == dist[v])   cnt[v] = (cnt[v] + cnt[u]) % MOD;   <- TANPA push
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
