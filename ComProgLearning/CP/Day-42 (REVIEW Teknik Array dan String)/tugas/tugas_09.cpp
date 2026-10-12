/*
============================================================
📋 TUGAS 09: Membaca Buku
============================================================
Source: Codeforces 279B
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Ada N buku berjajar. Membaca buku ke-i butuh a[i] menit. Seseorang memilih
satu titik awal, lalu membaca buku-buku BERURUTAN ke kanan sampai waktunya
habis. Total waktunya T menit.

Cari jumlah buku terbanyak yang bisa ia baca.

INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= T <= 10^9
- 1 <= a[i] <= 10^4

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
8 15
7 2 3 4 5 15 2 7
output:
4
penjelasan: buku ke-2 sampai ke-5: 2+3+4+5 = 14.

SAMPLE 2 - tidak ada yang muat
input:
1 1
100
output:
0
penjelasan: jawaban 0 itu sah.

SAMPLE 3 - semuanya muat
input:
4 4
1 1 1 1
output:
4

SAMPLE 4 - hanya satu yang muat
input:
3 5
5 5 5
output:
1

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- semua a[i] positif -> pendekatan dua pointer sah
- jawaban 0 mungkin, jangan mengasumsikan minimal 1
- perhatikan bahwa ia harus membaca BERURUTAN, tidak boleh melompat
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
