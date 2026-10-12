/*
============================================================
📋 TUGAS 05: Posisi Subarray Terbaik
============================================================
Source: Original
Difficulty: Easy
Topics: kadane + pelacakan indeks, tie-breaking

PROBLEM:
Cari subarray TIDAK KOSONG dengan jumlah maksimum, lalu cetak indeks
awal dan akhirnya (1-based, inklusif).

ATURAN SERI (baca pelan-pelan, ini inti soalnya):
  1. kalau ada beberapa subarray dengan jumlah maksimum yang sama,
     pilih yang PALING PENDEK
  2. kalau masih seri juga, pilih yang PALING KIRI

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Dua bilangan dipisah spasi

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - jawaban tunggal
input:
5
1 2 -10 3 4
output:
4 5
penjelasan: [3,4] = 7 mengalahkan [1,2] = 3.

SAMPLE 2 - tiga kandidat seri, aturan panjang menentukan
input:
6
2 -1 2 -5 3 0
output:
5 5
penjelasan: ada TIGA subarray dengan jumlah 3:
  [1..3] = 2-1+2 = 3   (panjang 3)
  [5..5] = 3           (panjang 1)  <- terpendek, ini jawabannya
  [5..6] = 3+0 = 3     (panjang 2)
Perhatikan [5..6]: menambah elemen 0 tidak mengubah jumlah tapi
memperpanjang subarray. Kadane naif sering ikut menelan nol di belakang.

SAMPLE 3 - semua negatif
input:
3
-4 -1 -9
output:
2 2
penjelasan: jawabannya elemen tunggal terbesar.

SAMPLE 4 - subarray membentang melewati nilai negatif
input:
4
5 -2 5 -2
output:
1 3
penjelasan: [5,-2,5] = 8. Ekor -2 di akhir harus dibuang, meski
cur sempat bernilai 6 di sana.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- curL hanya diperbarui SAAT reset, bukan di setiap iterasi
- untuk "terpendek", pakai > pada perbandingan best, lalu bandingkan
  panjang saat nilainya sama persis
- elemen 0 di ujung tidak boleh ikut terbawa
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Aturan tie-breaking mengubah operator perbandingan yang kamu pakai.

    return 0;
}
