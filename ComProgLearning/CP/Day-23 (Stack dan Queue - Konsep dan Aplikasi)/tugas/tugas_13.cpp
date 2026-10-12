/*
============================================================
📋 TUGAS 13: Stack — Next Smaller Element
============================================================
Source: Classic
Difficulty: Hard
Topics: monotonic stack

PROBLEM:
Diberikan array N bilangan. Untuk setiap elemen, cari elemen
PERTAMA di SEBELAH KANAN yang nilainya LEBIH KECIL (strictly less).
Jika tidak ada, output -1.

INPUT:
- Baris pertama: integer N
- Baris kedua: N integer

OUTPUT:
- N integer: next smaller element untuk setiap posisi

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
4 2 1 5 3

SAMPLE OUTPUT:
2 1 -1 3 -1

SAMPLE INPUT 2:
4
1 2 3 4

SAMPLE OUTPUT 2:
-1 -1 -1 -1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Mirip next greater, tapi pop saat arr[top] > arr[i]

    return 0;
}
