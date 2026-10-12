/*
============================================================
📋 TUGAS 04: Boleh Kosong vs Tidak Boleh Kosong
============================================================
Source: Original
Difficulty: Easy
Topics: edge case kadane, inisialisasi best

PROBLEM:
Diberikan T kasus uji, masing-masing sebuah array. Untuk setiap array
cetak DUA bilangan pada satu baris:
  1. jumlah subarray maksimum kalau subarray TIDAK boleh kosong
  2. jumlah subarray maksimum kalau subarray BOLEH kosong

Soal ini sengaja memaksamu menulis kedua versi berdampingan, supaya
perbedaannya terasa bukan sekadar dihafal.

INPUT FORMAT:
- Baris pertama: T
- Setiap kasus: satu baris berisi N diikuti N bilangan

OUTPUT FORMAT:
- T baris, masing-masing dua bilangan dipisah spasi

CONSTRAINTS:
- 1 <= T <= 100
- total N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - empat kasus sekaligus
input:
4
3 -5 -2 -9
3 1 -2 3
1 -1
3 0 -5 0
output:
-2 0
3 3
-1 0
0 0
penjelasan per baris:
  [-5,-2,-9]  semua negatif -> kedua jawaban BERBEDA. Ini satu-satunya
              situasi yang membedakan keduanya.
  [1,-2,3]    ada positif -> kedua jawaban SAMA. Berlaku umum: begitu
              ada satu elemen >= 0, kedua versi pasti seragam.
  [-1]        kasus N = 1 yang negatif.
  [0,-5,0]    nol itu tidak negatif, jadi kedua versi menjawab 0.
              Perhatikan: jangan pakai kondisi a[i] > 0 untuk mendeteksi
              "ada elemen tidak negatif".
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- versi tidak boleh kosong: best = LLONG_MIN, cur = max(x, cur+x)
- versi boleh kosong:       best = 0,         cur = max(0LL, cur+x)
- reset kedua variabel di SETIAP kasus uji (bug klasik multi-testcase)
- elemen bernilai 0 tidak boleh diperlakukan seperti negatif
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Satu perbedaan: inisialisasi best.

    return 0;
}
