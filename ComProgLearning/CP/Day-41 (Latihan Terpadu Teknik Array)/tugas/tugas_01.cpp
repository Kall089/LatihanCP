/*
============================================================
📋 TUGAS 01: Subarray Sums I
============================================================
Source: CSES 1660
Difficulty: Easy
Topics: two pointers (Day 32)

PROBLEM:
Diberikan N bilangan bulat POSITIF. Hitung ada berapa subarray yang
jumlahnya tepat X.

Karena semua elemen positif, memperlebar subarray SELALU menaikkan
jumlahnya. Sifat monoton itulah yang membuat two pointers sah di sini.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= X, a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6 7
2 4 1 2 7 1
output:
3
penjelasan: [2,4,1], [4,1,2], dan [7].

SAMPLE 2 - banyak elemen kembar
input:
4 2
1 1 1 1
output:
3
penjelasan: [1,1] pada posisi (1,2), (2,3), (3,4).

SAMPLE 3 - N = 1
input:
1 5
5
output:
1

SAMPLE 4 - seluruh array
input:
3 9
3 3 3
output:
1
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- jawabannya bisa sampai ~10^10, pakai long long
- two pointers valid HANYA karena semua elemen positif. Kalau soal
  mengizinkan 0 atau negatif, pendekatan ini rusak (lihat tugas 02)
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
