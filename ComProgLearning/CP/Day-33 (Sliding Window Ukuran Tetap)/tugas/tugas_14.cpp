/*
 * Day 20 — Sliding Window
 * File  : tugas_14.cpp
 * Topik : Longest Substring with At Most 2 Distinct Characters
 * Tingkat: Hard ★★★☆☆
 * -----------------------------------------------
 * Diberikan string s. Cari panjang SUBSTRING TERPANJANG yang mengandung
 * paling banyak 2 karakter berbeda.
 *
 * Ini kasus khusus dari "K distinct" dengan K=2 yang tujuannya:
 * pastikan paham polanya dan bisa kembangkan ke K umum.
 *
 * Pendekatan: variable-size window + freq map (sama seperti exercise_4
 * dengan K=2).
 *
 * Input format  : Satu baris berisi string s (huruf kecil)
 * Output format : panjang substring terpanjang
 * Constraints   : 1 ≤ |s| ≤ 200.000
 *                 huruf kecil saja
 *
 * Sample Input 1:        Sample Output 1:
 * eceba                  3
 *
 * Sample Input 2:        Sample Output 2:
 * ccaabbb                5
 *
 * Sample Input 3:        Sample Output 3:
 * aaa                    3
 *
 * NOTE Sample 1: "ece" panjang 3 dengan {e,c}.
 * NOTE Sample 2: "aabbb" panjang 5 dengan {a,b}.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: variable-size window dengan freq map, batas K=2

    return 0;
}
