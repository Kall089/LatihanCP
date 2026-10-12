#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 4: Perampok Rumah Melingkar
 *
 * Sama seperti Latihan 3, tetapi rumah-rumahnya membentuk LINGKARAN: rumah
 * pertama dan rumah terakhir juga bertetangga.
 *
 * Batas: 1 <= N <= 2*10^5, 0 <= a[i] <= 10^9
 *
// Test Case 1:
// Input:
// 4
// 2 1 1 2
// Output:
// 3
// (rumah 0 dan 3 kini bertetangga, jadi 4 tidak lagi boleh)
//
// Test Case 2:
// Input:
// 3
// 1 2 3
// Output:
// 3
//
// Test Case 3 (satu rumah - kasus khusus yang wajib ditangani):
// Input:
// 1
// 9
// Output:
// 9
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Jalankan versi LINEAR dua kali: pada a[0..n-2] dan pada a[1..n-1],
    // lalu ambil max. JANGAN menambal rekurens dengan if.
    // n == 1 harus ditangani terpisah (rentang kosong).
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
