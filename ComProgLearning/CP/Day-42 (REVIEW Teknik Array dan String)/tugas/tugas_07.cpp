/*
============================================================
📋 TUGAS 07: Elemen Lebih Besar Berikutnya (Melingkar)
============================================================
Source: LeetCode 503
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan array MELINGKAR berisi N bilangan: setelah elemen terakhir kembali
ke elemen pertama. Untuk setiap elemen, cari elemen pertama yang LEBIH BESAR
darinya saat berjalan ke kanan secara melingkar. Kalau tidak ada, cetak -1.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N bilangan dipisah spasi

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
3
1 2 1
output:
2 -1 2
penjelasan: elemen ke-3 menemukan 2 setelah membungkus.

SAMPLE 2 - menurun
input:
5
5 4 3 2 1
output:
-1 5 5 5 5
penjelasan: semua kecuali yang terbesar menemukan 5 setelah membungkus.

SAMPLE 3 - semua kembar
input:
3
3 3 3
output:
-1 -1 -1
penjelasan: 'lebih besar' bersifat ketat.

SAMPLE 4 - menaik
input:
5
1 5 3 6 8
output:
5 6 6 8 -1

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- trik umum: jalankan loop sebanyak 2N kali, tapi hanya SIMPAN jawaban
  untuk indeks i % N
- jangan benar-benar menduplikasi arraynya kalau tidak perlu
- setiap elemen tetap masuk struktur bantu satu kali
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
