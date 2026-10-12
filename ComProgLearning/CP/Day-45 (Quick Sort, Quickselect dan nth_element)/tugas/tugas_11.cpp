/*
============================================================
📋 TUGAS 11: Median Bergerak
============================================================
Source: Original
Difficulty: Hard
Topics: dua heap

PROBLEM:
Diberikan array N bilangan dan ukuran jendela M. Untuk setiap posisi
jendela, cetak median elemen di dalamnya. Untuk M genap, ambil elemen
tengah yang lebih kecil.

INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N-M+1 bilangan

CONSTRAINTS:
- 1 <= M <= N <= 2*10^5

SAMPLE INPUT 1:
5 3
1 3 2 5 4

SAMPLE OUTPUT 1:
2 3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Quickselect TIDAK cocok di sini karena harus dijalankan ulang tiap langkah. Pakai dua heap (max untuk separuh bawah, min untuk separuh atas) dengan penghapusan tertunda, atau multiset dengan iterator tengah.

    return 0;
}
