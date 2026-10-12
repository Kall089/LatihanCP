/*
============================================================
📋 TUGAS 13: Penjadwalan Tiga Kriteria
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Tie-break berlapis pada penjadwalan

PROBLEM:
Ada n pekerjaan dengan prioritas p[i], durasi d[i], dan nomor urut masuk.
Aturan penjadwalan: prioritas LEBIH BESAR dikerjakan lebih dulu; kalau prioritas sama
durasi LEBIH PENDEK lebih dulu; kalau keduanya sama nomor urut LEBIH KECIL lebih dulu.
Cetak jumlah waktu selesai seluruh pekerjaan.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: p[i] dan d[i]

OUTPUT FORMAT:
Satu bilangan: jumlah seluruh waktu selesai

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= p[i] <= 10, 1 <= d[i] <= 10^9

SAMPLE INPUT 1:
4
2 3
1 1
2 1
1 5

SAMPLE OUTPUT 1:
20
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Batasan p paling besar 10 adalah petunjuk keras bahwa seri akan sering terjadi. Perhatikan bahwa jumlah waktu selesai bisa mencapai 2*10^14.

    return 0;
}
