/*
============================================================
📋 TUGAS 13: Subarray Terpendek dengan Jumlah Minimal K
============================================================
Source: LeetCode 862
Difficulty: Hard
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan bulat yang BOLEH NEGATIF dan bilangan K. Cari panjang
subarray terpendek yang jumlahnya minimal K. Kalau tidak ada, cetak -1.

Bandingkan dengan tugas 04. Di sana semua elemen positif dan two pointers
cukup. Di sini tidak - dan alasannya patut kamu pahami sebelum menulis kode.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan, atau -1

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= K <= 10^9
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - negatif di tengah
input:
3 3
2 -1 2
output:
3
penjelasan: seluruh array. Perhatikan bahwa [2] saja tidak cukup dan [2,-1] lebih kecil.

SAMPLE 2 - tidak ada
input:
2 4
1 2
output:
-1

SAMPLE 3 - kasus panjang
input:
5 167
84 -37 32 40 95
output:
3
penjelasan: subarray [32,40,95].

SAMPLE 4 - N = 1
input:
1 1
1
output:
1

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kenapa two pointers gagal: dengan elemen negatif, memperlebar window tidak
  lagi menjamin jumlahnya naik, sehingga pointer kiri tidak bisa maju dengan aman
- pendekatan yang benar: prefix sum + struktur yang menjaga prefix MENAIK
- buang dari depan yang sudah memenuhi (jawabannya sudah dicatat), buang dari
  belakang yang nilainya tidak lebih baik daripada prefix baru
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
