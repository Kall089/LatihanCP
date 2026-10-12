/*
============================================================
📋 TUGAS 02: Apartemen
============================================================
Source: CSES 1084
Difficulty: Easy
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Ada N pelamar dan M apartemen. Pelamar ke-i menginginkan apartemen berukuran
sekitar a[i], dan ia menerima apartemen berukuran antara a[i]-K sampai a[i]+K.
Setiap pelamar dapat paling banyak satu apartemen, dan setiap apartemen
diberikan ke paling banyak satu pelamar.

Cari jumlah pelamar maksimum yang bisa mendapat apartemen.

INPUT FORMAT:
- Baris pertama: N, M, dan K
- Baris kedua: N bilangan, keinginan pelamar
- Baris ketiga: M bilangan, ukuran apartemen

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N, M <= 2*10^5
- 0 <= K <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
4 3 5
60 45 80 60
30 60 75
output:
2

SAMPLE 2 - tidak ada yang cocok
input:
1 1 5
10
100
output:
0

SAMPLE 3 - K = 0
input:
2 2 0
10 10
10 10
output:
2
penjelasan: dengan K=0, ukurannya harus sama persis.

SAMPLE 4 - banyak pelamar satu apartemen
input:
3 1 1
1 2 3
3
output:
1
penjelasan: apartemen ukuran 3 cocok untuk pelamar 2 dan 3, tapi hanya bisa diberikan ke satu orang.

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- urutkan KEDUA daftar, lalu jalankan dua pointer bersamaan
- greedy: selalu berikan apartemen terkecil yang masih layak
- jangan lupa apartemen yang terlalu kecil harus dilewati, bukan menghentikan loop
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
