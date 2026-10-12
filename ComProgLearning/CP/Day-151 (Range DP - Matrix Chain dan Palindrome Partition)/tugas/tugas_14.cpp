/*
============================================================
📋 TUGAS 14: Pewarnaan Strip Kertas (Strange Printer)
============================================================
Source: LeetCode 664 (Strange Printer)
Difficulty: Hard
Topics: Range DP Segment Coloring

PROBLEM:
Terdapat sebuah printer aneh yang dapat mencetak serangkaian huruf pada sebuah strip kertas.
Dalam satu kali operasi cetak, printer dapat mencetak huruf yang sama pada sembarang rentang
kontigu [l, r], dan huruf baru tersebut akan menimpa (overwrite) huruf apa pun yang sudah ada sebelumnya.
Awalnya strip kertas kosong (semua spasi).
Diberikan target string S. Tentukan jumlah operasi cetak MINIMUM yang diperlukan untuk menghasilkan string S.

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Satu bilangan bulat: jumlah operasi cetak minimum.

CONSTRAINTS:
1 <= |S| <= 100
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
aaabbb

SAMPLE OUTPUT 1:
2
(Penjelasan: Cetak "aaaaaa", lalu timpa dengan "bbb" di belakang -> "aaabbb". Butuh 2 operasi)

SAMPLE INPUT 2:
aba

SAMPLE OUTPUT 2:
2
(Penjelasan: Cetak "aaa", lalu timpa 'b' di tengah -> "aba". Butuh 2 operasi)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.size();

    // TODO: Selesaikan Strange Printer dengan Range DP
    // dp[l][r] = langkah minimum mencetak S[l..r]
    // dp[l][r] = dp[l][r-1] jika s[r] == s[r-1]
    // jika tidak: min over k dari l s.d. r-1:
    // jika s[k] == s[r]: dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r-1])

    return 0;
}
