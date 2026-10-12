/*
============================================================
📋 TUGAS 14: Nested Ranges Count
============================================================
Source: CSES 2169
Difficulty: Hard
Topics: Sorting multi-kriteria + BIT

PROBLEM:
Diberikan n rentang [a, b]. Untuk setiap rentang, hitung berapa rentang lain yang
MEMUATNYA, dan berapa rentang lain yang DIMUAT olehnya.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a dan b

OUTPUT FORMAT:
Baris 1: n bilangan (berapa rentang memuat rentang ke-i)
Baris 2: n bilangan (berapa rentang dimuat rentang ke-i)

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a <= b <= 10^9

SAMPLE INPUT 1:
4
1 6
2 4
4 8
3 6

SAMPLE OUTPUT 1:
0 1 0 1
2 0 0 0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Butuh Fenwick Tree (Day 170, sudah kamu kerjakan) dan kompresi koordinat (Day 40). Kuncinya adalah aturan pengurutan saat a atau b bernilai sama — pikirkan baik-baik.

    return 0;
}
