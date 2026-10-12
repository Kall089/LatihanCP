/*
 * Day 20 — Sliding Window
 * File  : tugas_09.cpp
 * Topik : Permutation in String (Fixed Window + Freq Match)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan dua string s1 dan s2 (huruf kecil saja).
 * Tentukan apakah s2 mengandung permutasi dari s1 sebagai SUBSTRING.
 * Kalau ada, output "YES", kalau tidak "NO".
 *
 * Pendekatan: fixed-size window berukuran |s1| di atas s2.
 * Bandingkan freq array (ukuran 26) — kalau sama → permutasi ditemukan.
 *
 * Trik optimasi: maintain matched_count yang hanya update saat ada
 * perubahan, tidak perlu compare freq array tiap iterasi.
 *
 * Input format  : Baris 1: string s1
 *                 Baris 2: string s2
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ |s1| ≤ |s2| ≤ 200.000
 *                 huruf kecil saja
 *
 * Sample Input 1:        Sample Output 1:
 * ab                     YES
 * eidbaooo
 *
 * Sample Input 2:        Sample Output 2:
 * ab                     NO
 * eidboaoo
 *
 * NOTE Sample 1: "ba" di s2 adalah permutasi dari "ab".
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: fixed window + freq matching

    return 0;
}
