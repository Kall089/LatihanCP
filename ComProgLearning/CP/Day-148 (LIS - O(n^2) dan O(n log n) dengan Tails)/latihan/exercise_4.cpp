#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 4: Rekonstruksi LIS
 *
 * Cetak panjang LIS (ketat naik) pada baris pertama, lalu SALAH SATU LIS yang
 * sah pada baris kedua (nilainya, dipisah spasi).
 *
 * Batas: 1 <= N <= 2*10^5, |a[i]| <= 10^9
 *
// Test Case 1:
// Input:
// 8
// 3 1 4 1 5 9 2 6
// Output:
// 4
// 1 4 5 9
// (jawaban lain yang sah, mis. 1 4 5 6, juga diterima)
//
// Test Case 2 (barisan tunggal):
// Input:
// 1
// 42
// Output:
// 1
// 42
//
// Test Case 3 (menurun - LIS panjangnya 1):
// Input:
// 4
// 4 3 2 1
// Output:
// 1
// 4
// (elemen mana pun diterima)
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // JANGAN mengembalikan isi tails -- itu bukan subsekuens yang sah.
    // Simpan idx[k] = indeks elemen yang saat ini mengisi tails[k],
    // dan par[i] = idx[p-1] saat elemen i mendarat di posisi p.
    // Telusuri balik dari idx.back().
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
