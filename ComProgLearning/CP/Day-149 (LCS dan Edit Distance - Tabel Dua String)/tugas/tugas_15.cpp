/*
============================================================
📋 TUGAS 15: Satu Program, Lima Jawaban
============================================================
Source: Latihan sintesis (penutup Day 149)
Difficulty: Hard
Topics: melihat bahwa semuanya tabel yang sama

PROBLEM:
Diberi dua string A dan B. Cetak LIMA bilangan, masing-masing di baris
sendiri, menggunakan sesedikit mungkin tabel DP:
  1. panjang LCS
  2. panjang substring bersama terpanjang
  3. edit distance (sisip/hapus/ganti, biaya 1)
  4. jumlah penghapusan minimum agar keduanya sama (hanya hapus)
  5. panjang supersequence bersama terpendek

INPUT: dua baris
OUTPUT: lima baris
CONSTRAINTS: 1 <= |A|, |B| <= 2000

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
abcde                3
ace                  1
                     2
                     2
                     5

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
sea                  2
eat                  2
                     2
                     2
                     4

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
abc                  0
xyz                  0
                     3
                     6
                     6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Nomor 1, 2, 4, 5 semuanya berasal dari satu tabel LCS (nomor 2 butuh
    // tabelnya sendiri karena aturan resetnya berbeda). Nomor 3 butuh tabel
    // edit distance.
    // Jadi minimal TIGA tabel -- dan menyadari mana yang bisa dibagi adalah
    // inti latihan ini.
    //   hapus minimum = n + m - 2*LCS
    //   panjang SCS   = n + m - LCS
    return 0;}
