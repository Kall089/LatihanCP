/*
============================================================
📋 TUGAS 06: Merangkai String Biner dari Kata Kunci
============================================================
Source: LeetCode 139 / CSES String Matching DP
Difficulty: Medium
Topics: Unbounded Word Segmentation

PROBLEM:
Diberikan sebuah string biner target S dengan panjang M, dan sebuah kamus
yang berisi N kata biner W[0], ..., W[N-1].
Setiap kata dalam kamus dapat digunakan berkali-kali tanpa batas.
Tentukan jumlah MINIMUM kata dari kamus yang harus disambungkan secara
berurutan agar menghasilkan tepat string S.
Jika mustahil membentuk string S, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan M.
Baris kedua berisi string target S (panjang M).
N baris berikutnya berisi kata-kata dalam kamus W[i].

OUTPUT FORMAT:
Satu bilangan bulat: jumlah minimum kata, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 100
1 <= M <= 5.000
1 <= panjang(W[i]) <= M
Karakter dalam string hanya '0' dan '1'.

SAMPLE INPUT 1:
3 7
1011010
101
10
1010

SAMPLE OUTPUT 1:
2
(Penjelasan: "101" + "1010" = "1011010", menggunakan 2 kata)

SAMPLE INPUT 2:
2 4
0000
01
10

SAMPLE OUTPUT 2:
-1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    string s;
    cin >> s;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    // TODO: Selesaikan dengan DP String Matching (Unbounded)
    // dp[i] = kosa kata minimum untuk membentuk prefix s[0...i-1]
    // dp[0] = 0
    // Untuk i dari 1 sampai m:
    //   Cek setiap word: jika i >= len(w) dan substring cocok, dp[i] = min(dp[i], dp[i - len(w)] + 1)

    return 0;
}
