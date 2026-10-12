/*
============================================================
📋 TUGAS 10: Maximum Sum Rectangle
============================================================
Source: UVa 108 (Maximum Sum)
Difficulty: Medium
Topics: kunci pasangan baris + kadane 1D

PROBLEM:
Diberikan matriks R x C berisi bilangan bulat (boleh negatif). Cari
SUBMATRIKS persegi panjang yang tidak kosong dengan jumlah seluruh
elemennya maksimum.

Ide kuncinya: submatriks ditentukan oleh (baris atas, baris bawah,
kolom kiri, kolom kanan). Kunci PASANGAN BARISNYA - ada O(R^2)
pasangan. Untuk tiap pasangan, jumlahkan tiap kolom di antara kedua
baris itu menjadi satu array 1D sepanjang C. Sekarang "pilih kolom
kiri dan kanan terbaik" persis masalah Kadane.

INPUT FORMAT:
- Baris pertama: R dan C
- R baris berikutnya: masing-masing C bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 300
- -10^4 <= m[i][j] <= 10^4

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
3 3
1 2 -1
-3 4 5
2 -1 3
output:
12
penjelasan: dua submatriks berbeda sama-sama bernilai 12 -
kolom 2..3 pada semua baris: (2-1)+(4+5)+(-1+3) = 1+9+2 = 12
seluruh matriks: 2+6+4 = 12
Keduanya benar, yang diminta hanya nilainya.

SAMPLE 2 - semua negatif
input:
2 2
-3 -1
-4 -2
output:
-1
penjelasan: submatriks tidak boleh kosong, jadi jawabannya adalah
sel tunggal terbesar. Kalau kodemu mencetak 0, Kadane 1D di dalamnya
memakai versi boleh-kosong.

SAMPLE 3 - matriks satu baris
input:
1 5
-2 5 -1 4 -3
output:
8
penjelasan: R = 1 membuat soal ini merosot jadi Kadane 1D murni:
[5,-1,4] = 8. Berguna untuk memastikan loop pasangan barismu tidak
melewatkan kasus r1 == r2.

SAMPLE 4 - matriks berselang-seling
input:
4 4
1 -2 3 4
-5 6 -7 8
9 -10 11 -12
2 3 -4 5
output:
12
penjelasan: tanda yang berganti-ganti membuat jawaban tidak berada di
pojok mana pun yang "kelihatan" besar. Gunakan sample ini untuk
memastikan kamu benar-benar mencoba SEMUA pasangan baris.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- Kadane 1D di dalamnya harus versi TIDAK BOLEH KOSONG
- akumulasi kolom secara inkremental saat r2 bertambah, jangan hitung
  ulang dari nol (kalau tidak, kompleksitasnya jadi O(R^2 * R * C))
- target O(R^2 * C) = 300*300*300 = 2.7*10^7, aman
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
    // Kunci batas baris, akumulasi kolom secara inkremental, lalu Kadane 1D.

    return 0;
}
