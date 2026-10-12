/*
============================================================
📋 TUGAS 10: Second Best MST
============================================================
Source: Original
Difficulty: Medium
Topics: Kruskal + variasi

PROBLEM:
Cari bobot minimum spanning tree KEDUA TERBAIK yang bobotnya BERBEDA dari
MST terbaik. Kalau tidak ada, cetak -1.

INPUT FORMAT:
- Baris pertama: N dan M
- M baris: u, v, w

OUTPUT FORMAT:
- Satu bilangan atau -1

CONSTRAINTS:
- 1 <= N <= 1000
- 1 <= M <= 5000

SAMPLE INPUT 1:
4 5
1 2 1
2 3 2
1 3 3
3 4 4
1 4 5

SAMPLE OUTPUT 1:
8
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bangun MST dulu, lalu untuk setiap sisi MST coba buang dan bangun ulang tanpa sisi itu. O(N*M log M) cukup untuk batas ini.

    return 0;
}
