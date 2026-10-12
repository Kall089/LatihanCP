/*
============================================================
📋 TUGAS 06: Merge K Sorted Lists
============================================================
Source: LeetCode 23
Difficulty: Medium
Topics: Heap gabung daftar

PROBLEM:
Diberikan k daftar bilangan yang masing-masing sudah terurut menaik. Gabungkan
seluruhnya menjadi satu daftar terurut.

INPUT FORMAT:
Baris 1: k
k baris berikutnya: panjang daftar lalu isinya

OUTPUT FORMAT:
Satu baris berisi seluruh bilangan hasil gabungan, terurut

CONSTRAINTS:
1 <= k <= 10^4, total elemen <= 10^5

SAMPLE INPUT 1:
3
3 1 4 5
2 1 3
2 2 6

SAMPLE OUTPUT 1:
1 1 2 3 4 5 6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Heap berisi (nilai, daftar mana, indeks ke berapa). O(N log k), jauh lebih baik daripada menggabungkan semuanya lalu mengurutkan ketika k kecil.

    return 0;
}
