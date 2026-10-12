/*
============================================================
📋 TUGAS 13: Menara Air
============================================================
Source: Original
Difficulty: Hard
Topics: ternary + simulasi

PROBLEM:
N kota berjajar pada garis lurus di posisi x[i] dengan populasi p[i].
Kamu membangun satu menara air di posisi t (bilangan real). Biaya totalnya
adalah jumlah p[i] * |x[i] - t| untuk seluruh kota. Cari biaya minimum.

INPUT FORMAT:
- Baris pertama: N
- N baris: x[i] dan p[i]

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 1 <= N <= 2*10^5

SAMPLE INPUT 1:
3
0 1
10 1
20 1

SAMPLE OUTPUT 1:
20.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Fungsi jumlah jarak berbobot bersifat cembung. Bisa ternary search, TETAPI ada solusi eksak: MEDIAN BERBOBOT. Kerjakan keduanya dan bandingkan.

    return 0;
}
