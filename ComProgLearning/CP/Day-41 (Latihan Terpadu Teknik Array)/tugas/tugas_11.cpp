/*
============================================================
📋 TUGAS 11: Max Consecutive Ones III
============================================================
Source: LeetCode 1004
Difficulty: Medium
Topics: sliding window variabel (Day 34)

PROBLEM:
Diberikan array berisi 0 dan 1. Kamu boleh mengubah PALING BANYAK K
buah angka 0 menjadi 1. Cari panjang rentang berurutan berisi 1 semua
yang terpanjang setelah perubahan itu.

Rumus ulang soalnya supaya jadi pola window standar: "cari rentang
terpanjang yang berisi paling banyak K buah nol". Merumuskan ulang
seperti ini adalah setengah dari pekerjaannya.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan (0 atau 1)

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= K <= N

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
11 2
1 1 1 0 0 0 1 1 1 1 0
output:
6
penjelasan: ubah dua nol pada posisi 5 dan 6 -> rentang posisi 5..10
sepanjang 6.

SAMPLE 2 - K = 0 dan tidak ada satu pun angka 1
input:
3 0
0 0 0
output:
0
penjelasan: jawaban 0 itu sah. Pastikan kodemu tidak mencetak 1.

SAMPLE 3 - K lebih besar dari jumlah nol
input:
3 2
1 1 1
output:
3

SAMPLE 4 - K cukup untuk semua nol
input:
6 3
0 0 1 1 0 0
output:
5
penjelasan: ada 4 nol, K = 3, jadi tidak semua bisa diubah. Rentang
terbaik panjangnya 5, bukan 6.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- pantau jumlah NOL di dalam window, bukan jumlah satu
- while (nol > K) kecilkan kiri
- K = 0 harus tetap bekerja
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
