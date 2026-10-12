/*
============================================================
📋 TUGAS 15: Patience Sorting — Cetak Tumpukannya
============================================================
Source: Klasik (asal-usul algoritma tails)
Difficulty: Hard
Topics: memahami tails secara fisik

PROBLEM:
Bagikan kartu satu per satu dari kiri ke kanan. Setiap kartu diletakkan di
tumpukan PALING KIRI yang kartu teratasnya >= nilai kartu itu; kalau tidak
ada, buat tumpukan baru di kanan.
Cetak banyaknya tumpukan, lalu isi setiap tumpukan (dari bawah ke atas).

INPUT: Baris 1 N; Baris 2 N bilangan
OUTPUT: Baris 1 jumlah tumpukan; lalu satu baris per tumpukan
CONSTRAINTS: 1 <= N <= 2*10^5

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
5                          3
3 1 4 1 5                  3 1 1
                           4
                           5

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
3                          1
3 2 1                      3 2 1

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          3
1 2 3                      1
                           2
                           3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Kartu teratas tiap tumpukan PERSIS array tails -- dan ia terurut menaik,
    // jadi tumpukan yang tepat dicari dengan binary search.
    // Banyaknya tumpukan = panjang LIS ketat. Kerjakan soal ini dan kamu tidak
    // akan pernah lagi lupa apa isi tails.
    return 0;}
