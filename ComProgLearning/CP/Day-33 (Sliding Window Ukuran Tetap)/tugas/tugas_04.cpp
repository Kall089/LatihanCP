/*
 * Day 20 — Sliding Window
 * File  : tugas_04.cpp
 * Topik : Find All Anagrams in a String (Fixed Window + Freq Match)
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan dua string s dan p (huruf kecil saja).
 * Cetak SEMUA index awal (0-indexed) di s dimana terdapat substring
 * yang merupakan ANAGRAM dari p. Index dipisah spasi (urut menaik).
 * Jika tidak ada, cetak baris kosong.
 *
 * Pendekatan: fixed-size window seukuran |p| + bandingkan freq array
 * (ukuran 26) antara window di s dan p.
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: string p
 * Output format : index-index awal anagram (dipisah spasi) atau baris kosong
 * Constraints   : 1 ≤ |p| ≤ |s| ≤ 200.000
 *                 huruf kecil saja
 *
 * Sample Input 1:        Sample Output 1:
 * cbaebabacd             0 6
 * abc
 *
 * Sample Input 2:        Sample Output 2:
 * abab                   0 1 2
 * ab
 *
 * NOTE Sample 1: di index 0 → "cba" (anagram "abc"); di index 6 → "bac" (anagram "abc").
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung freq[26] untuk p, lalu sliding fixed window di s
    // bandingkan have[26] dengan need[26] tiap kali window penuh

    return 0;
}
