/*
============================================================
📋 TUGAS 06: Maximum Sum Circular Subarray
============================================================
Source: LeetCode 918
Difficulty: Medium
Topics: melingkar, membelah ruang jawaban

PROBLEM:
Array MELINGKAR berisi N bilangan: setelah elemen terakhir kembali ke
elemen pertama. Cari subarray TIDAK KOSONG dengan jumlah maksimum,
di mana subarray boleh membungkus melewati ujung. Subarray tetap tidak
boleh memakai satu elemen lebih dari sekali.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 3*10^4
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - jawaban membungkus
input:
5
5 -3 5 -3 5
output:
12
penjelasan: ambil [5(idx5), 5(idx1), -3, 5] -> 5+5-3+5 = 12.
Lewat rumus: total = 9, subarray minimum = -3, jadi 9-(-3) = 12,
mengalahkan kadane biasa yang cuma 7.

SAMPLE 2 - SEMUA NEGATIF, ini jebakannya
input:
3
-3 -2 -3
output:
-2
penjelasan: total = -8, subarray minimum = -8, sehingga
total - min = 0. Tapi 0 berarti "tidak mengambil apa-apa" alias
subarray KOSONG, yang dilarang. Penjaganya: kalau kadane biasa
menghasilkan nilai negatif, langsung kembalikan nilai itu.

SAMPLE 3 - N kecil dengan wrap
input:
3
5 -3 5
output:
10
penjelasan: [5(idx3), 5(idx1)] membungkus lewat ujung = 10.

SAMPLE 4 - semua positif
input:
4
3 1 2 4
output:
10
penjelasan: seluruh array. Pastikan kodemu tidak malah menghitung
total - min lalu membuang elemen padahal tidak perlu.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- jawaban = max(kadaneMax, total - kadaneMin)
- PENJAGA: if (kadaneMax < 0) return kadaneMax;
- jangan menduplikasi array jadi 2N lalu Kadane biasa - itu SALAH,
  karena bisa menghasilkan subarray lebih panjang dari N
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // max(kadane, total - kadaneMin), TAPI cek kasus semua negatif.

    return 0;
}
