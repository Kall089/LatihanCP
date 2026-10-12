/*
 * Day 20 — Sliding Window
 * File  : tugas_03.cpp
 * Topik : Count Vowels in Window of Size K
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan string s (huruf kecil saja) dan integer K.
 * Untuk setiap substring kontinu berukuran tepat K, hitung jumlah HURUF VOKAL
 * (a, e, i, o, u) di substring tersebut. Cetak BANYAK MAKSIMUM vokal di
 * antara semua substring berukuran K.
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: integer K
 * Output format : satu integer (max vokal di window K)
 * Constraints   : 1 ≤ K ≤ |s| ≤ 200.000
 *                 s hanya berisi huruf kecil 'a'..'z'
 *
 * Sample Input 1:        Sample Output 1:
 * abciiidef              3
 * 3
 *
 * Sample Input 2:        Sample Output 2:
 * aeiou                  2
 * 2
 *
 * Sample Input 3:        Sample Output 3:
 * leetcode               2
 * 3
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: maintain count vokal di window, slide tambah/kurangi
    // Hint: helper bool isVowel(char c) { return c=='a'||c=='e'||... }

    return 0;
}
