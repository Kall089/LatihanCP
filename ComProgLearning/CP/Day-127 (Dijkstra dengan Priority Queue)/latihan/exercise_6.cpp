#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 6: Tiket Diskon (Dijkstra Berlapis)
 *
 * Graf BERARAH berbobot non-negatif. Kamu punya K kupon; setiap kupon
 * MENGGRATISKAN biaya satu edge. Cari biaya minimum dari 1 ke N dengan
 * memakai paling banyak K kupon. Cetak -1 jika tak terjangkau.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= K <= 10, 0 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 4 4 1
// 1 2 3
// 2 4 10
// 1 3 5
// 3 4 5
// Output:
// 3
// (1-2-4 dengan kupon di edge 2->4: 3 + 0 = 3)
//
// Test Case 2 (K = 0, jadi Dijkstra biasa):
// Input:
// 4 4 0
// 1 2 3
// 2 4 10
// 1 3 5
// 3 4 5
// Output:
// 10
//
// Test Case 3 (kupon lebih banyak dari edge yang ada):
// Input:
// 3 2 5
// 1 2 8
// 2 3 8
// Output:
// 0
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // dist[v][k] = biaya minimum ke v dengan k kupon TERPAKAI.
    // Dua relaksasi per edge: bayar (k tetap), atau pakai kupon (k+1, biaya 0).
    // Jawaban = min over k dari dist[N][k].
    // Cara pandangnya: ini Dijkstra biasa pada graf BERLAPIS (K+1 salinan),
    // bukan Dijkstra yang ditambal.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
