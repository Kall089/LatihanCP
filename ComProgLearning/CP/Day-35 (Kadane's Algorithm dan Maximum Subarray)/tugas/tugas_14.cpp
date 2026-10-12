/*
============================================================
📋 TUGAS 14: Jumlah Maksimum Tepat K Segmen
============================================================
Source: Original
Difficulty: Hard
Topics: DP generalisasi kadane

PROBLEM:
Pilih TEPAT K subarray yang saling TIDAK tumpang tindih (semuanya
tidak kosong) sehingga total jumlahnya maksimum. Kedua segmen BOLEH
bersebelahan. Dijamin 1 <= K <= N.

Soal ini memperlihatkan Kadane sebagai kasus khusus: Kadane adalah
soal ini dengan K = 1.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= K <= N <= 5000
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
5 2
1 -2 3 -2 4
output:
7
penjelasan: ambil [3] dan [4] -> 7. Sama seperti tugas 09, tapi di
sini jumlah segmennya bisa lebih dari dua.

SAMPLE 2 - K = N, semua elemen terpaksa terpakai
input:
4 4
-1 -2 -3 -4
output:
-10
penjelasan: dengan K = N, setiap elemen harus menjadi segmennya
sendiri. Tidak ada pilihan, jawabannya total array. Jawaban negatif
itu sah - jangan pasang lantai nol.

SAMPLE 3 - K = 1, ini Kadane biasa
input:
5 1
-3 -1 -2 -5 -4
output:
-1
penjelasan: K = 1 mereduksi soal ini menjadi Kadane tidak-boleh-kosong.
Pakai sample ini untuk memverifikasi bahwa DP kamu benar di kasus
paling sederhana sebelum menguji K besar.

SAMPLE 4 - tiga segmen
input:
6 3
3 -1 4 -1 5 -9
output:
12
penjelasan: [3], [4], [5] -> 12. Perhatikan bahwa menyambung semuanya
jadi [3,-1,4,-1,5] hanya memberi 10, jadi memecahnya justru lebih baik.

SAMPLE 5 - segmen bersebelahan itu sah
input:
4 2
1 2 3 4
output:
10
penjelasan: semua elemen positif, jadi ambil seluruh array dan
belah jadi dua segmen bersebelahan, misalnya [1,2] dan [3,4].
Totalnya tetap 10. Kalau kodemu memaksa ada jeda minimal satu elemen
di antara segmen, kamu akan menjawab 9 dan itu salah menurut soal ini.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- dp[j][i][0] = elemen ke-i TIDAK dalam segmen ke-j
  dp[j][i][1] = elemen ke-i berada DI DALAM segmen ke-j
- state tak-terjangkau harus bernilai sentinel negatif besar, dan
  jangan sampai sentinel itu overflow saat ditambah a[i]
- O(N*K) = 5000*5000 = 2.5*10^7, aman. Tapi array 3 dimensi penuh
  akan boros memori - gulung dimensi j
- verifikasi dengan K = 1 dulu (sample 3)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // dp[i][j] dengan dua sub-state: elemen ke-i ikut segmen ke-j atau tidak. Kadane adalah kasus K = 1.

    return 0;
}
