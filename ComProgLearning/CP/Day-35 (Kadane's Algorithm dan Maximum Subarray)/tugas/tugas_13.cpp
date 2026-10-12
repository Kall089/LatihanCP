/*
============================================================
📋 TUGAS 13: Subarray Maksimum Setelah K Pengulangan
============================================================
Source: Original
Difficulty: Hard
Topics: kadane + analisis tanda total

PROBLEM:
Array a sepanjang N diulang sebanyak K kali secara berurutan, menjadi
array sepanjang N*K. Cari jumlah subarray maksimum pada array hasil
pengulangan itu. Subarray BOLEH KOSONG (jawaban minimal 0). Cetak
hasilnya modulo 1000000007.

Karena N*K bisa mencapai 10^14, kamu jelas tidak boleh membangun
arraynya. Perhatikan bahwa subarray terbaik hanya punya dua bentuk:
seluruhnya di dalam dua salinan pertama, atau berbentuk
(sufiks terbaik) + (beberapa salinan penuh di tengah) + (prefiks terbaik).

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan, hasil modulo 1000000007

CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= K <= 10^9
- -10^4 <= a[i] <= 10^4

------------------------------------------------------------
SAMPLE 1 - total array bernilai 0
input:
3 3
1 -2 1
output:
2
penjelasan: array hasilnya [1,-2,1, 1,-2,1, 1,-2,1]. Total per salinan
adalah 0, jadi menambah salinan di tengah tidak menolong. Yang terbaik
adalah sufiks [1] disambung prefiks [1] = 2, tepat di perbatasan antara
dua salinan.

SAMPLE 2 - total positif, sambungkan semuanya
input:
3 2
1 2 3
output:
12
penjelasan: total = 6 dan positif, jadi ambil seluruh array yang
sudah diulang: 6*2 = 12.

SAMPLE 3 - semua negatif
input:
2 5
-1 -2
output:
0
penjelasan: subarray boleh kosong, jadi jawabannya 0. Jangan lupa
lantai nol ini.

SAMPLE 4 - K besar, jawaban wajib dimodulo
input:
3 1000000000
2 -1 3
output:
999999979
penjelasan: total per salinan = 4 dan positif, jadi jawaban
sebenarnya = 4 * 10^9. Lalu 4000000000 mod 1000000007 = 999999979.
Sample ini menguji dua hal sekaligus: rumus untuk K besar, dan
apakah kamu memodulo di akhir. Hitung dulu dalam long long, modulo
BELAKANGAN - jangan memodulo di tengah perbandingan max, karena
modulo merusak urutan.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- K = 1 harus ditangani terpisah (tidak ada perbatasan)
- untuk K >= 2: max(kadane pada dua salinan,
                     prefiksTerbaik + sufiksTerbaik + (K-2)*max(0,total))
- prefiks dan sufiks terbaik memakai versi BOLEH KOSONG (minimal 0)
- jangan pernah membandingkan nilai yang sudah dimodulo
- hasil akhir bisa negatif? tidak, karena boleh kosong -> minimal 0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kalau K >= 2, jawabannya melibatkan sufiks terbaik + tengah yang diulang + prefiks terbaik. Perhatikan tanda total array.

    return 0;
}
