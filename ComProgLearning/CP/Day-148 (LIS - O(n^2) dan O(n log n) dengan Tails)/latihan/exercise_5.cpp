#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 5: Menghitung Banyak LIS
 *
 * Cetak dua bilangan: panjang LIS (ketat naik), dan ADA BERAPA subsekuens
 * berbeda yang mencapai panjang itu (modulo 10^9+7).
 * Dua subsekuens dianggap berbeda kalau himpunan INDEKSNYA berbeda.
 *
 * Batas: 1 <= N <= 2000, |a[i]| <= 10^9
 *
// Test Case 1:
// Input:
// 5
// 1 3 5 4 7
// Output:
// 4 2
// (1 3 5 7 dan 1 3 4 7)
//
// Test Case 2 (semua sama - tiap elemen adalah LIS sendiri):
// Input:
// 3
// 2 2 2
// Output:
// 1 3
//
// Test Case 3:
// Input:
// 6
// 1 2 4 3 5 4
// Output:
// 4 3
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // len[i] dan cnt[i] bersamaan:
    //   len[j]+1 >  len[i]  -> len[i] = len[j]+1 ; cnt[i] = cnt[j]   (SALIN)
    //   len[j]+1 == len[i]  -> cnt[i] += cnt[j]                       (TAMBAH)
    // Jawaban = jumlah cnt[i] untuk semua i dengan len[i] maksimum.
    // Pola SALIN/TAMBAH ini sama persis dengan menghitung jalur terpendek
    // di Day 127.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
