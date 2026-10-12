/*
============================================================
📋 TUGAS 07: Last Stone Weight
============================================================
Source: LeetCode 1046
Difficulty: Easy
Topics: Max-heap

PROBLEM:
Ada n batu dengan berat a[i]. Berulang kali ambil DUA batu terberat x dan y (x >= y):
jika x sama dengan y keduanya hancur; jika tidak, keduanya hancur dan muncul batu baru
berberat x - y. Cetak berat batu yang tersisa, atau 0 kalau tidak ada.

INPUT FORMAT:
Baris 1: n
Baris 2: n berat a[i]

OUTPUT FORMAT:
Satu bilangan: berat batu tersisa, atau 0

CONSTRAINTS:
1 <= n <= 30, 1 <= a[i] <= 1000

SAMPLE INPUT 1:
6
2 7 4 1 8 1

SAMPLE OUTPUT 1:
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kali ini MAX-heap. Perhatikan bahwa keputusanmu tetap menghasilkan kandidat baru — itu tanda heap, bukan sort.

    return 0;
}
