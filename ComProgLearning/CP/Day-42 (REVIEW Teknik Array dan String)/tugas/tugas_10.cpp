/*
============================================================
📋 TUGAS 10: Deret Berurutan Terpanjang
============================================================
Source: LeetCode 128
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan bulat (boleh tidak terurut, boleh ada duplikat). Cari
panjang deret bilangan BERURUTAN (misalnya 3,4,5,6) terpanjang yang seluruh
anggotanya ada di dalam array. Posisi di dalam array tidak penting.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6
100 4 200 1 3 2
output:
4
penjelasan: deret 1,2,3,4.

SAMPLE 2 - semua duplikat
input:
3
1 1 1
output:
1

SAMPLE 3 - N = 1
input:
1
9
output:
1

SAMPLE 4 - ada duplikat di dalam deret
input:
4
1 2 0 1
output:
3
penjelasan: deret 0,1,2. Duplikat tidak menambah panjang.

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- soal ini TIDAK meminta berurutan di dalam array, jadi kamu boleh mengubah
  urutannya
- ada dua solusi bersih: sort lalu sapu, atau hash set dengan trik
  "hanya mulai menghitung dari x yang x-1 nya tidak ada"
- duplikat harus ditangani, jangan sampai memperpanjang deret
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
