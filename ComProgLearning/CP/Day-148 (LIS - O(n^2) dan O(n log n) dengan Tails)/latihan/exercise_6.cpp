#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 6: Menumpuk Kotak (LIS yang Menyamar)
 *
 * Ada N kotak berukuran (w, h). Kotak A boleh ditumpuk DI DALAM kotak B jika
 * w_A < w_B DAN h_A < h_B (keduanya harus KETAT). Cari rantai terpanjang.
 *
 * Batas: 1 <= N <= 2*10^5, 1 <= w, h <= 10^9
 *
// Test Case 1:
// Input:
// 4
// 5 4
// 6 4
// 6 7
// 2 3
// Output:
// 3
// (2,3) -> (5,4) -> (6,7)
//
// Test Case 2 (lebar sama semua - hanya satu yang boleh dipakai):
// Input:
// 3
// 1 1
// 1 2
// 1 3
// Output:
// 1
//
// Test Case 3 (rantai penuh):
// Input:
// 3
// 1 1
// 2 2
// 3 3
// Output:
// 3
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Urutkan w MENAIK; kalau w SAMA, urutkan h MENURUN.
    // Lalu cari LIS KETAT pada barisan h.
    // Tie-break MENURUN itu wajib: ia membuat dua kotak selebar sama menjadi
    // barisan h yang menurun, sehingga LIS ketat otomatis hanya mengambil satu.
    // Test Case 2 menguji tepat hal ini -- tanpa tie-break terbalik kamu akan
    // menjawab 3.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
