/*
 * Day 20 — Sliding Window
 * File  : tugas_15.cpp
 * Topik : Maximum Number of Vowels in Substring of Given Length
 * Tingkat: Hard ★★☆☆☆ (LeetCode 1456 — sebenarnya medium, dipakai sebagai bonus)
 * -----------------------------------------------
 * Diberikan string s (huruf kecil) dan integer K.
 * Cari banyak HURUF VOKAL maksimum di antara semua substring kontinu
 * berukuran tepat K.
 *
 * Pendekatan: fixed-size sliding window (mirip tugas_03 tapi K besar).
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: integer K
 * Output format : satu integer (max banyak vokal)
 * Constraints   : 1 ≤ K ≤ |s| ≤ 200.000
 *                 huruf kecil saja
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
 *
 * Sample Input 4:        Sample Output 4:
 * rhythms                0
 * 4
 *
 * NOTE Sample 4: "rhythms" tidak ada vokal (a,e,i,o,u) sama sekali.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: fixed-size window untuk count vokal
    // Hint: helper isVowel(c), atau cek c == 'a' || 'e' || 'i' || 'o' || 'u'

    return 0;
}
