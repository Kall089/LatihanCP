/*
============================================================
📋 TUGAS 08: Trapping Rain Water
============================================================
Source: LeetCode 42
Difficulty: Medium
Topics: two pointers ATAU monotonic stack (Day 32 / 36)

PROBLEM:
Diberikan N batang dengan lebar 1 dan tinggi h[i], membentuk sebuah
permukaan. Setelah hujan, air akan tertahan di cekungan-cekungannya.
Hitung total volume air yang tertahan.

Air di atas kolom i setinggi min(tertinggi di kiri, tertinggi di kanan)
dikurangi h[i]. Soal ini punya dua solusi elegan yang sama-sama O(n);
kerjakan salah satu, lalu pahami yang lain.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan tinggi

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= h[i] <= 10^5

------------------------------------------------------------
SAMPLE 1 - kasus klasik
input:
12
0 1 0 2 1 0 1 3 2 1 2 1
output:
6

SAMPLE 2 - cekungan dalam
input:
6
4 2 0 3 2 5
output:
9

SAMPLE 3 - permukaan rata
input:
3
3 3 3
output:
0
penjelasan: tidak ada cekungan.

SAMPLE 4 - menurun terus
input:
5
5 4 3 2 1
output:
0
penjelasan: air tidak bisa tertahan tanpa dinding di kanan. Sample ini
menangkap kesalahan "cuma melihat maksimum di kiri".
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- versi two pointers: gerakkan pointer dari sisi yang dindingnya
  LEBIH PENDEK - itu yang menentukan tinggi air
- versi prefix: hitung maxKiri[] dan maxKanan[] dulu, lalu jumlahkan
  min(keduanya) - h[i]
- hasilnya bisa besar, pakai long long
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
