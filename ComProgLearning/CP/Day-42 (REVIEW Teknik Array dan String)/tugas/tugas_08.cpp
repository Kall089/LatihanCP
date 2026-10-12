/*
============================================================
📋 TUGAS 08: Kelipatan pada Subarray
============================================================
Source: LeetCode 523
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan bulat non-negatif dan bilangan K. Tentukan apakah ada
subarray dengan PANJANG MINIMAL DUA yang jumlahnya merupakan kelipatan K.
Cetak "YA" atau "TIDAK".

Perhatikan bahwa 0 adalah kelipatan dari bilangan apa pun.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- YA atau TIDAK

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= K <= 10^9
- 0 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - ada
input:
5 6
23 2 4 6 7
output:
YA
penjelasan: subarray [2,4] berjumlah 6.

SAMPLE 2 - tidak ada
input:
5 13
23 2 6 4 7
output:
TIDAK

SAMPLE 3 - panjang 2 tapi tidak kelipatan
input:
2 5
1 0
output:
TIDAK

SAMPLE 4 - dua nol
input:
2 7
0 0
output:
YA
penjelasan: 0 adalah kelipatan 7. Sample ini sering terlewat.

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- syarat PANJANG MINIMAL DUA adalah inti soal ini; tanpa syarat itu jawabannya
  akan sering YA secara sepele
- simpan sisa prefix beserta INDEKS pertamanya, lalu cek jaraknya >= 2
- cnt/map harus berisi (sisa 0, indeks -1) di awal
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
