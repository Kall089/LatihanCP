#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 5: Jalur dengan Edge Termahal Seminimal Mungkin (Minimax)
 *
 * Graf TAK BERARAH. Setiap edge punya "ketinggian" h. Biaya sebuah jalur
 * BUKAN jumlah, melainkan ketinggian TERBESAR di sepanjang jalur itu.
 * Cari biaya minimum dari 1 ke N. Cetak -1 jika tak terjangkau.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= h <= 10^9
 *
// Test Case 1:
// Input:
// 4 4
// 1 2 10
// 2 4 10
// 1 3 3
// 3 4 8
// Output:
// 8
// (lewat 1-3-4: max(3,8) = 8, lebih kecil daripada max(10,10) = 10)
//
// Test Case 2 (satu edge langsung):
// Input:
// 2 1
// 1 2 7
// Output:
// 7
//
// Test Case 3 (tak terjangkau):
// Input:
// 3 1
// 1 2 4
// Output:
// -1
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Satu-satunya perubahan dari Dijkstra biasa:
    //     nd = max(dist[u], w)     bukan     nd = dist[u] + w
    // Kebenarannya tetap terjaga karena max(a,w) >= a -- sifat yang sama
    // dengan "bobot non-negatif tidak pernah memperpendek".
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
