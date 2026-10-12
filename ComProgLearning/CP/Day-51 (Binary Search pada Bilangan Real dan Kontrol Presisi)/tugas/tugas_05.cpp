/*
============================================================
📋 TUGAS 05: Solve It
============================================================
Source: UVa 10341
Difficulty: Easy
Topics: akar persamaan monoton

PROBLEM:
Diberikan p, q, r, s, t, u, cari x pada [0, 1] yang memenuhi
p*e^(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x^2 + u = 0.
Dijamin fungsinya menurun pada [0,1]. Cetak dengan 4 desimal, atau
'No solution' kalau tidak ada akar di rentang itu.

INPUT FORMAT:
- Beberapa kasus: enam bilangan p q r s t u per baris

OUTPUT FORMAT:
- Satu baris per kasus

CONSTRAINTS:
- 0 <= p,r <= 20
- -20 <= q,s,t <= 0

SAMPLE INPUT 1:
0 0 0 0 -2 1

SAMPLE OUTPUT 1:
0.7071
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Cek dulu tanda f(0) dan f(1). Kalau f(0) < 0 atau f(1) > 0, tidak ada solusi.

    return 0;
}
