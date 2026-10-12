#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 6: Kadane + Rekonstruksi Indeks
 *
 * Diberi array N bilangan (boleh negatif). Cari subarray TIDAK KOSONG dengan
 * jumlah maksimum. Cetak jumlahnya, lalu indeks awal dan akhir (0-indexed).
 * Jika ada beberapa jawaban, cetak yang indeks awalnya paling kecil.
 *
 * Batas: 1 <= N <= 2*10^5, |a[i]| <= 10^9
 *
// Test Case 1:
// Input:
// 9
// -2 1 -3 4 -1 2 1 -5 4
// Output:
// 6
// 3 6
//
// Test Case 2 (SEMUA NEGATIF - jebakan best = 0):
// Input:
// 3
// -5 -2 -9
// Output:
// -2
// 1 1
//
// Test Case 3 (semua positif, seluruh array):
// Input:
// 4
// 1 2 3 4
// Output:
// 10
// 0 3
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // cur = max(a[i], cur + a[i]); best = max(best, cur);
    // best DIINISIALISASI a[0], BUKAN 0. Test Case 2 mengujinya.
    // s diperbarui HANYA saat mulai ulang; bs/be HANYA saat rekor baru.
    // Untuk "indeks awal terkecil", pakai perbandingan KETAT (cur > best).
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
