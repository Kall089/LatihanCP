/*
 * Day 20 — Sliding Window
 * File  : tugas_11.cpp
 * Topik : Minimum Window Substring (Hard)
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan dua string s dan t. Cari SUBSTRING TERPENDEK dari s yang
 * mengandung SEMUA karakter t (termasuk multiplisitas — duplikat).
 * Output substring tersebut. Jika tidak ada, output "" (string kosong).
 * Jika ada beberapa dengan panjang sama, output yang paling kiri.
 *
 * Pendekatan: variable-size sliding window dengan freq map dan
 * counter "matched" karakter.
 *   - need[c] = freq c di t
 *   - have[c] = freq c di window
 *   - matched = jumlah karakter yang sudah punya count >= need
 *   - Saat matched == |unique chars in t| → window valid, coba shrink
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: string t
 * Output format : substring minimum, atau "" (string kosong)
 * Constraints   : 1 ≤ |s|, |t| ≤ 200.000
 *                 huruf kecil dan besar bisa muncul (bedakan!)
 *
 * Sample Input 1:        Sample Output 1:
 * ADOBECODEBANC          BANC
 * ABC
 *
 * Sample Input 2:        Sample Output 2:
 * a                      a
 * a
 *
 * Sample Input 3:        Sample Output 3:
 * a
 * aa                     (output baris kosong)
 *
 * NOTE Sample 3: t butuh 2 'a', tapi s hanya punya 1 → tidak mungkin.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sliding window dengan need/have/matched
    // Output: s.substr(start, len)

    return 0;
}
