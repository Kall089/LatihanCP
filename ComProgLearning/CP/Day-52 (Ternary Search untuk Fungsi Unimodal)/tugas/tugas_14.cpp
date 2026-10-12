/*
============================================================
📋 TUGAS 14: Lingkaran Terkecil Melingkupi
============================================================
Source: Original
Difficulty: Hard
Topics: ternary bersarang 2D

PROBLEM:
Diberikan N titik pada bidang, cari lingkaran TERKECIL yang memuat seluruh
titik. Cetak jari-jarinya dengan 6 desimal.

INPUT FORMAT:
- Baris pertama: N
- N baris berisi x dan y

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 1 <= N <= 1000

SAMPLE INPUT 1:
3
0 0
2 0
1 1

SAMPLE OUTPUT 1:
1.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // f(x,y) = jarak maksimum ke seluruh titik. Ini maksimum dari fungsi-fungsi cembung, jadi cembung. Ternary bersarang bekerja tetapi lambat; algoritma Welzl memberi O(n) yang diharapkan.

    return 0;
}
