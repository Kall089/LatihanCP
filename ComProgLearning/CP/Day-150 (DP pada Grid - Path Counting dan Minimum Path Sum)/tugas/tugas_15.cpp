/*
============================================================
📋 TUGAS 15: Satu Grid, Empat Jawaban
============================================================
Source: Latihan sintesis (penutup Day 150)
Difficulty: Hard
Topics: satu kerangka, banyak operator gabung

PROBLEM:
Grid R x C berisi bilangan; -1 berarti tembok. Dengan gerakan kanan/bawah,
cetak EMPAT bilangan, masing-masing di baris sendiri:
  1. banyak jalur (mod 10^9+7)
  2. jumlah jalur MINIMUM, atau -1 kalau tidak ada jalur
  3. jumlah jalur MAKSIMUM, atau -1
  4. banyak jalur yang mencapai jumlah MINIMUM (mod 10^9+7), atau 0

INPUT: Baris 1 R C; R baris berisi C bilangan
OUTPUT: empat baris
CONSTRAINTS: 1 <= R, C <= 1000

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
2 2                  2
1 1                  3
1 1                  3
                     2

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
2 2                  0
1 -1                 -1
-1 1                 -1
                     0

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
2 3                  3
1 2 3                12
4 5 6                16
                     1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Satu sapuan, empat array. Perhatikan bahwa setiap pertanyaan memakai
    // SENTINEL yang berbeda:
    //   hitung  -> 0     (identitas +)
    //   minimum -> +INF  (identitas min)
    //   maksimum-> -INF  (identitas max)
    // dan untuk nomor 4 pakai pola SALIN/TAMBAH yang sama seperti Day 127:
    //   nilai baru lebih kecil -> SALIN jumlahnya
    //   nilai baru sama        -> TAMBAHKAN jumlahnya
    // Kalau kamu bisa menulis ini dalam satu loop, kamu sudah menguasai
    // seluruh Day 120 + Day 150.
    return 0;}
