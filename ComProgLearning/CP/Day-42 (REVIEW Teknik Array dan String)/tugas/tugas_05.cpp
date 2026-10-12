/*
============================================================
📋 TUGAS 05: Rata-rata Tertinggi Panjang K
============================================================
Source: LeetCode 643
Difficulty: Easy
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan dan K. Cari JUMLAH terbesar dari subarray yang
panjangnya tepat K. (Karena panjangnya tetap, jumlah terbesar setara dengan
rata-rata tertinggi, tapi jumlah lebih aman karena bilangan bulat.)

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= K <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6 4
1 12 -5 -6 50 3
output:
51

SAMPLE 2 - N = K = 1
input:
1 1
5
output:
5

SAMPLE 3 - semua negatif
input:
3 2
-1 -2 -3
output:
-3
penjelasan: jawaban negatif itu sah; jangan pasang lantai nol.

SAMPLE 4 - K = 1
input:
5 1
0 4 0 3 2
output:
4

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- jangan hitung ulang K elemen tiap langkah; itu O(NK)
- jumlah bisa 2*10^14, pakai long long
- best diinisialisasi dari jendela PERTAMA, bukan dari 0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TEBAKAN TEKNIK SAYA: ______________________
    // SINYAL DI SOAL     : ______________________

    // TODO: Kerjakan di sini

    return 0;
}
