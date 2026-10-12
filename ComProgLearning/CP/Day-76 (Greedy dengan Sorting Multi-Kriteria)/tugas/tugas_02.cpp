/*
============================================================
📋 TUGAS 02: Nested Ranges Count
============================================================
Source: CSES 2169
Difficulty: Hard
Topics: Dominasi + BIT

PROBLEM:
Diberikan n rentang [a, b]. Untuk setiap rentang, hitung BERAPA BANYAK rentang lain
yang memuatnya, dan berapa banyak yang dimuatnya.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a dan b

OUTPUT FORMAT:
Baris 1: n bilangan (banyaknya rentang yang dimuat oleh rentang ke-i)
Baris 2: n bilangan (banyaknya rentang yang memuat rentang ke-i)

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a <= b <= 10^9

SAMPLE INPUT 1:
4
1 6
2 4
4 8
3 6

SAMPLE OUTPUT 1:
2 0 0 0
0 1 0 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Versi menghitung dari Tugas 01. Butuh Fenwick Tree (Day 170) dan kompresi koordinat (Day 38). Tie-break saat a seri menentukan apakah rentang identik terhitung — pikirkan baik-baik.

    return 0;
}
