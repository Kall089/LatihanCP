#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 4: Apakah Urutan Topologisnya Unik?
 *
 * Diberikan graf berarah N simpul, M edge.
 * Cetak:
 *   "SIKLUS"     jika tidak ada urutan topologis sama sekali
 *   "UNIK"       jika hanya ada tepat satu urutan topologis
 *   "BANYAK"     jika ada lebih dari satu
 *
 * Batas: 1 <= N, M <= 2*10^5
 *
// Test Case 1:
// Input:
// 3 2
// 1 2
// 2 3
// Output:
// UNIK
//
// Test Case 2:
// Input:
// 3 1
// 1 2
// Output:
// BANYAK
// (simpul 3 bebas ditaruh di mana saja)
//
// Test Case 3:
// Input:
// 4 4
// 1 2
// 2 3
// 3 4
// 4 1
// Output:
// SIKLUS
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Kunci: jika pada suatu iterasi antrean berisi >= 2 simpul,
    // berarti ada minimal dua urutan yang sah.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
