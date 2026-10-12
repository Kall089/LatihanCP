/*
============================================================
📋 TUGAS 06: Rentang Harga Saham
============================================================
Source: LeetCode 901
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan harga saham selama N hari berturut-turut. Untuk setiap hari i,
hitung SPAN-nya: berapa banyak hari berturut-turut sampai ke belakang
(termasuk hari i sendiri) yang harganya tidak melebihi harga hari i.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N bilangan dipisah spasi

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= harga <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
7
100 80 60 70 60 75 85
output:
1 1 1 2 1 4 6

SAMPLE 2 - menaik
input:
4
1 2 3 4
output:
1 2 3 4

SAMPLE 3 - menurun
input:
4
4 3 2 1
output:
1 1 1 1

SAMPLE 4 - semua kembar
input:
3
5 5 5
output:
1 2 3
penjelasan: 'tidak melebihi' berarti yang SAMA ikut dihitung. Kalau kamu memakai kondisi ketat, jawabanmu jadi 1 1 1.

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- sample 4 menentukan apakah kamu memakai < atau <=
- struktur yang kamu pakai menyimpan indeks, dan setiap indeks masuk sekali
- kalau kamu menulis dua loop bersarang, itu O(N^2) dan akan TLE
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
