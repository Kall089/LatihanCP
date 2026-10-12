/*
============================================================
📋 TUGAS 13: Substring dengan Tepat K Karakter Berbeda
============================================================
Source: Original (varian LeetCode 992)
Difficulty: Hard
Topics: sliding window + trik "paling banyak K" (Day 34 + 40)

PROBLEM:
Diberikan string S sepanjang N yang hanya berisi huruf kecil. Hitung
ada berapa substring yang mengandung TEPAT K karakter berbeda.

Menghitung "tepat K" secara langsung dengan sliding window itu sulit,
karena kondisinya tidak monoton. Tapi "paling banyak K" ITU monoton
dan mudah. Dari situ:

    tepat(K) = palingBanyak(K) - palingBanyak(K-1)

Trik pengurangan ini muncul terus di soal counting. Layak dihafal.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: string S

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= K <= 26
- 1 <= N <= 2*10^5

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
5 2
pqpqs
output:
7
penjelasan: substring dengan tepat 2 karakter berbeda: "pq", "pqp",
"pqpq", "qp", "qpq", "pq", "qs".

SAMPLE 2 - K lebih besar dari jumlah karakter berbeda
input:
5 3
aabab
output:
0
penjelasan: string ini hanya punya 2 karakter berbeda, jadi tidak ada
substring dengan tepat 3. Jawaban 0 sah - pastikan kodemu tidak
mengembalikan nilai negatif dari pengurangan.

SAMPLE 3 - semua karakter sama
input:
4 1
aaaa
output:
10
penjelasan: semua 10 substring punya tepat 1 karakter berbeda.

SAMPLE 4 - semua karakter berbeda
input:
3 3
abc
output:
1
penjelasan: hanya seluruh string.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- tulis SATU fungsi palingBanyak(k), panggil dua kali
- di dalamnya, banyaknya substring yang berakhir di r dan valid
  adalah r - l + 1. Menjumlahkan itu memberi totalnya
- palingBanyak(0) harus mengembalikan 0
- jawabannya bisa ~2*10^10, pakai long long
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
