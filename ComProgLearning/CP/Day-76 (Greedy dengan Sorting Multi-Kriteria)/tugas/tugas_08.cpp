/*
============================================================
📋 TUGAS 08: Menghitung Pasangan Terurut
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Dominasi + inversi

PROBLEM:
Diberikan n pasangan (a[i], b[i]). Hitung berapa banyak pasangan indeks (i, j) dengan
i berbeda dari j yang memenuhi a[i] <= a[j] DAN b[i] <= b[j].

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a[i] dan b[i]

OUTPUT FORMAT:
Satu bilangan: banyaknya pasangan

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a[i], b[i] <= 10^9

SAMPLE INPUT 1:
3
1 1
1 2
2 1

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perhatikan bahwa pertidaksamaannya TIDAK strict, sehingga nilai yang seri terhitung. Itu mengubah tie-break yang tepat. Butuh BIT (Day 170) dan kompresi koordinat (Day 38).

    return 0;
}
