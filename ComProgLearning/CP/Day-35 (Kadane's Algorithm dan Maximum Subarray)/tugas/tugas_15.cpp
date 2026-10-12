/*
============================================================
📋 TUGAS 15: Submatriks Maksimum Melingkar
============================================================
Source: Original
Difficulty: Hard
Topics: kadane 2D + melingkar, menggabungkan dua teknik

PROBLEM:
Diberikan matriks R x C yang MELINGKAR pada arah kolom: setelah kolom
terakhir kembali ke kolom pertama. Cari submatriks tidak kosong dengan
jumlah maksimum, di mana batas kolomnya boleh membungkus. Batas
barisnya TIDAK melingkar. Setiap sel tetap tidak boleh dipakai lebih
dari sekali.

Soal ini adalah gabungan tugas 06 dan tugas 10. Kalau keduanya sudah
kamu kuasai, soal ini hanya soal menyusun keduanya dengan urutan yang
benar.

INPUT FORMAT:
- Baris pertama: R dan C
- R baris berikutnya: masing-masing C bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 200
- -10^4 <= m[i][j] <= 10^4

------------------------------------------------------------
SAMPLE 1 - jawaban membungkus lewat kolom
input:
2 3
1 -5 2
3 -4 1
output:
7
penjelasan: ambil kedua baris, kolom 3 lalu membungkus ke kolom 1.
Jumlah kolom untuk baris 1..2 adalah [4,-9,3]. Kadane melingkar pada
[4,-9,3]: total = -2, minimum = -9, jadi -2-(-9) = 7.

SAMPLE 2 - satu baris, semua negatif
input:
1 4
-3 -1 -4 -1
output:
-1
penjelasan: menguji dua hal sekaligus - R = 1, dan penjaga
semua-negatif pada Kadane melingkar. Jawaban 0 berarti penjagamu
tidak ada.

SAMPLE 3 - matriks lebih besar dengan wrap
input:
3 3
2 -6 3
-1 -7 4
5 -8 1
output:
14
penjelasan: kolom tengah sangat merugikan di semua baris, sehingga
jawaban terbaik membungkus dari kolom 3 ke kolom 1 melewatinya.

SAMPLE 4 - semua positif
input:
2 2
1 2
3 4
output:
10
penjelasan: seluruh matriks. Pastikan logika melingkar kamu tidak
malah membuang kolom padahal semuanya menguntungkan.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- urutannya: kunci pasangan baris DULU, baru Kadane melingkar pada
  array kolom hasil kompresi
- Kadane melingkar butuh dua hal: kadaneMax, dan total - kadaneMin
- PENJAGA semua-negatif wajib ada di setiap pasangan baris, bukan
  cuma sekali di akhir
- target O(R^2 * C) = 200*200*200 = 8*10^6, aman
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kunci batas baris seperti biasa, lalu terapkan Kadane MELINGKAR pada array kolom. Ingat penjaga kasus semua negatif.

    return 0;
}
