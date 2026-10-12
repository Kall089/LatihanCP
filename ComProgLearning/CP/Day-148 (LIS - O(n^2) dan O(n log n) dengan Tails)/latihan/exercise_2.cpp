#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 2: LIS Versi O(n log n) dengan Tails
 *
 * Sama seperti Latihan 1, tetapi N jauh lebih besar sehingga O(N^2) TLE.
 * Cetak panjang subsekuens naik KETAT terpanjang.
 *
 * Batas: 1 <= N <= 2*10^5, |a[i]| <= 10^9
 *
// Test Case 1:
// Input:
// 8
// 3 1 4 1 5 9 2 6
// Output:
// 4
// (mis. 1 4 5 9 atau 1 4 5 6)
//
// Test Case 2 (sudah terurut naik):
// Input:
// 6
// 1 2 3 4 5 6
// Output:
// 6
//
// Test Case 3 (semua sama - menguji lower_bound):
// Input:
// 4
// 7 7 7 7
// Output:
// 1
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // tails[k] = EKOR TERKECIL di antara subsekuens naik berpanjang k+1.
    // lower_bound untuk versi KETAT. Test Case 3 mengujinya: jawabannya 1,
    // bukan 4.
    // INGAT: isi tails BUKAN LIS-nya; hanya ukurannya yang benar.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
