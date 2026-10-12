/*
============================================================
📋 TUGAS 14: Hirschberg — LCS dengan Memori Linear
============================================================
Source: Algoritma klasik (Hirschberg 1975)
Difficulty: Hard
Topics: divide and conquer + rolling array

PROBLEM:
Cetak SALAH SATU LCS dari dua string, dengan memori O(min(|A|,|B|)).
Tabel penuh tidak boleh dipakai.

INPUT: dua baris
OUTPUT: satu string
CONSTRAINTS: 1 <= |A|, |B| <= 10^4

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
abcbdab              bcba
bdcaba
(jawaban lain sepanjang 4 juga diterima)

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
abcde                ace
ace

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
xyz                  (baris kosong)
abc
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // IDE: potong A di tengah (baris mid). Hitung baris LCS dari kiri untuk
    // A[0..mid) dan baris LCS dari kanan untuk A[mid..n) yang dibalik --
    // keduanya dengan rolling array O(m). Titik potong terbaik di B adalah k
    // yang memaksimalkan kiri[k] + kanan[m-k]. Rekursi pada kedua bagian.
    // Waktu tetap O(n*m) (deret geometri), memori O(m).
    // Ini contoh terbaik bahwa "rekonstruksi butuh tabel penuh" bukan hukum
    // alam -- ia hanya default yang paling mudah.
    return 0;}
