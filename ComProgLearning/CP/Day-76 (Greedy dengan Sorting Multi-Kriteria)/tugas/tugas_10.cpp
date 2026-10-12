/*
============================================================
📋 TUGAS 10: Rentang Maksimal Tanpa Dominasi
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Pareto front + rekonstruksi

PROBLEM:
Diberikan n titik (x, y). Cetak seluruh titik yang PARETO-OPTIMAL (tidak didominasi
oleh titik lain), terurut menaik menurut x, lalu menaik menurut y.
Dua titik identik tidak saling mendominasi, jadi keduanya Pareto-optimal.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: x dan y

OUTPUT FORMAT:
Baris 1: banyaknya titik Pareto-optimal
Baris berikutnya: masing-masing satu titik

CONSTRAINTS:
1 <= n <= 2*10^5, 0 <= x, y <= 10^9

SAMPLE INPUT 1:
5
1 5
2 3
1 2
3 4
2 3

SAMPLE OUTPUT 1:
2
1 5
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bedakan pembanding di dalam kelompok x sama dan terhadap kelompok x lebih besar. Uji dengan koordinat 0..3 agar seri sering terjadi.

    return 0;
}
