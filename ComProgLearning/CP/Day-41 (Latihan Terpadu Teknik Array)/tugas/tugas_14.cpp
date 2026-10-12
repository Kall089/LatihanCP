/*
============================================================
📋 TUGAS 14: Submatriks dengan Jumlah Maksimum
============================================================
Source: Original (klasik, setara UVa 108)
Difficulty: Medium
Topics: prefix sum kolom (Day 30) + Kadane (Day 35)

PROBLEM:
Diberikan matriks R x C berisi bilangan bulat (boleh negatif). Cari
submatriks persegi panjang tidak kosong dengan jumlah maksimum.

Soal ini muncul lagi di sini karena ia adalah contoh paling bersih dari
"kunci sebagian, sisanya jadi soal 1D yang sudah dikenal". Kerjakan
ulang dari nol tanpa melihat catatan Day 35.

INPUT FORMAT:
- Baris pertama: R dan C
- R baris berikutnya: masing-masing C bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 300
- -10^4 <= m[i][j] <= 10^4

------------------------------------------------------------
SAMPLE 1 - kasus klasik
input:
3 4
1 2 -1 -4
-8 -3 4 2
3 8 10 -8
output:
21
penjelasan: baris 3 saja, kolom 1..3: 3 + 8 + 10 = 21. Perhatikan bahwa
submatriks terbaik ternyata hanya SATU baris - jangan berasumsi jawabannya
selalu memakai banyak baris.

SAMPLE 2 - semua negatif
input:
2 2
-1 -2
-3 -4
output:
-1
penjelasan: submatriks tidak boleh kosong, jadi ambil sel terbesar.
Kadane 1D di dalamnya harus versi TIDAK boleh kosong.

SAMPLE 3 - satu baris
input:
1 3
2 -1 3
output:
4
penjelasan: R = 1 mereduksi soal ini jadi Kadane murni.

SAMPLE 4 - semua positif
input:
2 3
1 1 1
1 1 1
output:
6
penjelasan: seluruh matriks.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kunci pasangan baris (r1, r2), akumulasi kolom SECARA INKREMENTAL
  saat r2 bertambah - jangan hitung ulang dari nol
- target O(R^2 * C), bukan O(R^2 * C^2)
- pastikan pasangan r1 == r2 ikut diuji
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
