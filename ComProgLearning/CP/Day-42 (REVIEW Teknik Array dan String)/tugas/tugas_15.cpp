/*
============================================================
📋 TUGAS 15: Median Jendela Geser
============================================================
Source: LeetCode 480
Difficulty: Hard
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan dan K GANJIL. Untuk setiap jendela berurutan berukuran
K, cetak MEDIAN-nya (nilai tengah setelah diurutkan).

Ini soal penutup blok. Ia menggabungkan gagasan jendela geser dengan struktur
data terurut, dan menuntutmu memilih struktur yang mendukung penghapusan
elemen sembarang - bukan hanya elemen terdepan.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N-K+1 bilangan dipisah spasi

CONSTRAINTS:
- 1 <= K <= N <= 2*10^5, K ganjil
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus klasik
input:
8 3
1 3 -1 -3 5 3 6 7
output:
1 -1 -1 3 5 6

SAMPLE 2 - K = 1
input:
5 1
1 2 3 4 5
output:
1 2 3 4 5
penjelasan: median jendela ukuran 1 adalah elemennya sendiri.

SAMPLE 3 - semua kembar
input:
4 3
5 5 5 5
output:
5 5
penjelasan: duplikat harus tetap ditangani; struktur yang menolak duplikat akan salah.

SAMPLE 4 - K = N
input:
5 5
9 1 8 2 7
output:
7

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- struktur yang paling sederhana: multiset + iterator yang menunjuk median,
  digeser satu langkah setiap penambahan/penghapusan
- alternatif klasik: dua heap (max-heap kiri, min-heap kanan) dengan
  penghapusan tertunda
- HATI-HATI menghapus dengan multiset::erase(nilai) - itu menghapus SEMUA
  yang bernilai sama. Pakai erase(find(nilai))
- 2*10^5 dengan log N aman; O(N*K log K) tidak
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
