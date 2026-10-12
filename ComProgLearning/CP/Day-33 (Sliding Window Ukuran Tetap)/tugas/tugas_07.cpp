/*
 * Day 20 — Sliding Window
 * File  : tugas_07.cpp
 * Topik : Longest Repeating Character Replacement
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan string s (huruf besar saja) dan integer K.
 * Kamu boleh mengganti maksimal K karakter di s dengan karakter lain.
 * Cari panjang SUBSTRING kontinu yang isinya bisa dibuat semua sama
 * setelah ganti maksimal K karakter.
 *
 * Pendekatan: variable-size sliding window.
 *   - freq[c] = count tiap huruf di window
 *   - max_freq = jumlah karakter dominan di window
 *   - window valid jika (window_size - max_freq) ≤ K
 *     (sisanya yang berbeda dengan dominan, bisa diganti)
 *   - Saat invalid, shrink L (cukup geser, tidak perlu re-compute max_freq)
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: integer K
 * Output format : panjang substring terpanjang
 * Constraints   : 1 ≤ |s| ≤ 200.000
 *                 0 ≤ K ≤ |s|
 *                 s hanya berisi huruf besar 'A'..'Z'
 *
 * Sample Input 1:        Sample Output 1:
 * ABAB                   4
 * 2
 *
 * Sample Input 2:        Sample Output 2:
 * AABABBA                4
 * 1
 *
 * NOTE Sample 1: ganti 2 'B' jadi 'A' → "AAAA", panjang 4.
 * NOTE Sample 2: ganti 1 char jadi → "AABBBBA" atau "ABABBBA" → window 4 yang valid.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sliding window, maintain freq[26] dan max_freq
    // window valid: (R - L + 1) - max_freq <= K

    return 0;
}
