/*
============================================================
📋 TUGAS 06: Substring Palindrom Terpanjang
============================================================
Source: Classic DP / LeetCode 5
Difficulty: Medium
Topics: Range DP Boolean, Substring Tracking

PROBLEM:
Diberikan sebuah string S. Tentukan panjang SUBSTRING palindrom TERPANJANG yang ada di dalam S.
Substring adalah barisan karakter berurutan dan kontigu di dalam string.

INPUT FORMAT:
Satu baris berisi satu string S tanpa spasi.

OUTPUT FORMAT:
Satu bilangan bulat: panjang substring palindrom terpanjang.

CONSTRAINTS:
1 <= |S| <= 2.000
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
babad

SAMPLE OUTPUT 1:
3
(Penjelasan: Substring "bab" atau "aba" memiliki panjang 3)

SAMPLE INPUT 2:
cbbd

SAMPLE OUTPUT 2:
2
(Penjelasan: Substring "bb" memiliki panjang 2)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.size();

    // TODO: Selesaikan Substring Palindrom Terpanjang dengan Range DP
    // vector<vector<bool>> is_pal(n, vector<bool>(n, false))
    // Perbarui max_len setiap kali menemukan substring palindrom

    return 0;
}
