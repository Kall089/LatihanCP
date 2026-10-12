/*
============================================================
📋 TUGAS 10: Menghapus Karakter Bersebelahan Identik
============================================================
Source: Codeforces 1132F (Clear the String) / Zuma DP
Difficulty: Hard
Topics: Range DP String Matching & Merging

PROBLEM:
Diberikan sebuah string S yang hanya terdiri dari huruf kecil.
Dalam satu langkah, kamu dapat memilih sebuah SUBSTRING yang semua karakternya SAMA,
lalu menghapusnya dari string. Sisa karakter di sebelah kiri dan kanannya akan langsung
menyatu kembali.
Tentukan jumlah langkah MINIMUM untuk menghapus SELURUH karakter di dalam string S
hingga string menjadi kosong.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N, menyatakan panjang string S.
Baris kedua berisi string S.

OUTPUT FORMAT:
Satu bilangan bulat: jumlah langkah minimum untuk menghapus seluruh string.

CONSTRAINTS:
1 <= N <= 500
S hanya berisi karakter huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
5
abaca

SAMPLE OUTPUT 1:
3
(Penjelasan: Hapus 'b' (sisa "aaca"), lalu hapus 'c' (sisa "aaa"), lalu hapus "aaa" sekaligus. Total 3 langkah)

SAMPLE INPUT 2:
3
abc

SAMPLE OUTPUT 2:
3

SAMPLE INPUT 3:
5
aaaaa

SAMPLE OUTPUT 3:
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    if (!(cin >> n >> s)) return 0;

    // TODO: Selesaikan Clear the String dengan Range DP
    // dp[l][r] = langkah minimum menghapus S[l..r]
    // dp[i][i] = 1
    // Transisi:
    // dp[l][r] = dp[l+1][r] + 1 (hapus s[l] sendirian)
    // Untuk k dari l+1 s.d. r:
    // Jika s[l] == s[k]:
    // dp[l][r] = min(dp[l][r], dp[l+1][k-1] + dp[k][r])

    return 0;
}
