/*
============================================================
📋 TUGAS 07: Maximum Product Subarray
============================================================
Source: LeetCode 152
Difficulty: Medium
Topics: kadane dua variabel

PROBLEM:
Cari subarray TIDAK KOSONG yang HASIL KALI seluruh elemennya paling
besar. Dijamin jawabannya muat di 64-bit bertanda.

Kenapa Kadane biasa gagal di sini: pada penjumlahan, nilai kecil
selamanya merugikan. Pada perkalian, nilai negatif besar justru ASET -
kalikan satu negatif lagi dan ia jadi positif terbesar.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^4
- -10 <= a[i] <= 10

------------------------------------------------------------
SAMPLE 1 - dua negatif saling meniadakan
input:
4
2 -3 -2 4
output:
48
penjelasan: seluruh array, 2*(-3)*(-2)*4 = 48. Kalau kamu hanya
melacak maksimum, saat bertemu -3 nilainya jatuh dan kamu akan
kehilangan jejak.

SAMPLE 2 - ada nol
input:
3
-2 0 -1
output:
0
penjelasan: nol memutus rantai. Setelah melewati 0, mx dan mn harus
kembali ke keadaan awal, dan 0 sendiri adalah kandidat jawaban.

SAMPLE 3 - jumlah negatif ganjil
input:
5
-1 -2 -3 -4 -5
output:
120
penjelasan: ada 5 negatif. Seluruh array menghasilkan -120, jadi satu
negatif harus dibuang. Membuang -1 (dari ujung kiri) memberi 120.
Perhatikan bahwa jawabannya BUKAN dari ujung kiri array.

SAMPLE 4 - N = 2 dengan nol
input:
2
-5 0
output:
0
penjelasan: pilihannya cuma -5, 0, atau 0. Jawabannya 0.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- lacak mx DAN mn secara bersamaan
- hitung keduanya dari nilai LAMA - simpan ke variabel sementara dulu.
  Menimpa mx lalu memakainya untuk menghitung mn adalah bug nomor satu
  di soal ini
- kandidatnya ada tiga: x, mx*x, mn*x
- pakai long long
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Lacak curMax dan curMin; tukar saat bertemu negatif.

    return 0;
}
