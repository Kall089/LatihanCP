#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 3: Ketat vs Tidak Menurun
 *
 * Diberi array N bilangan. Cetak DUA bilangan pada satu baris:
 *   (a) panjang subsekuens naik KETAT terpanjang        (a < b)
 *   (b) panjang subsekuens TIDAK MENURUN terpanjang     (a <= b)
 * Keduanya harus O(N log N).
 *
 * Batas: 1 <= N <= 2*10^5, |a[i]| <= 10^9
 *
// Test Case 1 (semua sama - pembeda paling tajam):
// Input:
// 3
// 1 1 1
// Output:
// 1 3
//
// Test Case 2:
// Input:
// 7
// 2 2 3 1 3 3 4
// Output:
// 3 6
// (ketat: 2 3 4 ; tidak menurun: 2 2 3 3 3 4)
//
// Test Case 3 (menurun tajam):
// Input:
// 4
// 9 5 5 1
// Output:
// 1 2
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // KETAT           -> lower_bound (menggantikan yang >= x)
    // TIDAK MENURUN   -> upper_bound (menggantikan yang >  x)
    // Kalau kamu tertukar, Test Case 1 langsung menangkapnya.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
