/*
============================================================
📋 TUGAS 14: Maximal Score After Removals
============================================================
Source: Original
Difficulty: Hard
Topics: stack, greedy, monotonic

PROBLEM:
Diberikan array A. Kamu bisa melakukan operasi berikut beberapa kali:
Pilih dua elemen bersebelahan a[i] dan a[i+1] di mana a[i] > a[i+1].
Hapus a[i+1] dan dapatkan skor sebesar a[i+1].
Hitung maksimum total skor yang bisa didapatkan.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer

OUTPUT FORMAT:
- Satu baris: long long (maksimum skor)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
5
5 2 4 1 3

SAMPLE OUTPUT 1:
10

SAMPLE INPUT 2:
4
1 2 3 4

SAMPLE OUTPUT 2:
0

NOTE: Elemen yang bisa dihapus = semua elemen yang bukan maksimum global dari kiri.
      Alias: semua elemen yang bukan prefix maximum.
      Jawaban = sum semua elemen - prefix_max_sum yang ≠ total.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
