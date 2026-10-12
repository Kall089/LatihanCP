/*
============================================================
📋 TUGAS 10: Penghapusan Digit
============================================================
Source: Latihan mandiri (LeetCode 402 - Remove K Digits)
Difficulty: Medium
Topics: Greedy dengan stack

PROBLEM:
Diberikan sebuah bilangan sebagai string sepanjang n dan bilangan k. Hapus tepat k
digit sehingga bilangan yang tersisa SEKECIL MUNGKIN (urutan digit yang tersisa tidak
boleh diubah). Cetak hasilnya tanpa nol di depan; jika kosong cetak 0.

INPUT FORMAT:
Baris 1: string bilangan
Baris 2: k

OUTPUT FORMAT:
Satu baris hasil

CONSTRAINTS:
1 <= n <= 10^5, 0 <= k <= n

SAMPLE INPUT 1:
1432219
3

SAMPLE OUTPUT 1:
1219
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Pikirkan sifat greedy: kalau sebuah digit lebih besar dari digit sesudahnya, menghapusnya selalu menguntungkan. Struktur data apa yang cocok untuk menerapkan aturan itu berulang kali?

    return 0;
}
