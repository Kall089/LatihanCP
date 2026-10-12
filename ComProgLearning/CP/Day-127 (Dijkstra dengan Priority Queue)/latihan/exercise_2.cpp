#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 2: Rekonstruksi Rute Terpendek
 *
 * Graf TAK BERARAH berbobot non-negatif. Cetak jarak terpendek 1 -> N pada
 * baris pertama, lalu urutan simpul rutenya pada baris kedua.
 * Cetak -1 saja jika tidak terjangkau.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 5 6
// 1 2 2
// 2 5 5
// 2 3 4
// 1 4 1
// 4 3 3
// 3 5 1
// Output:
// 5
// 1 4 3 5
//
// Test Case 2 (edge langsung paling murah):
// Input:
// 3 3
// 1 2 10
// 2 3 10
// 1 3 1
// Output:
// 1
// 1 3
//
// Test Case 3 (tak terjangkau):
// Input:
// 4 1
// 1 2 5
// Output:
// -1
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // GRAF TAK BERARAH: push kedua arah saat membaca input.
    // par[v] diperbarui HANYA di dalam if relaksasi.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
