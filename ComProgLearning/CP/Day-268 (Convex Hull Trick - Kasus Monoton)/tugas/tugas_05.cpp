/*
============================================================
📋 TUGAS 05: Penjadwalan Mesin dengan Setup Time Kuadratik
============================================================
Source: Scheduling Theory CHT
Difficulty: Hard
Topics: Convex Hull Trick, Quadratic DP

PROBLEM:
Terdapat N batch pekerjaan yang harus diproses oleh sebuah mesin manufaktur secara berurutan dari 1 sampai N.
Waktu tiba pekerjaan adalah t[0] <= t[1] <= ... <= t[N-1].
Pekerjaan dapat dikelompokkan ke dalam beberapa sesi pemrosesan.
Jika sesi pemrosesan mencakup pekerjaan dari j+1 sampai i, waktu setup mesin dan penundaan menghasilkan biaya:
`Cost(j+1, i) = S + (t[i] - t[j+1])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk menyelesaikan seluruh N pekerjaan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan S.
Baris kedua berisi N bilangan bulat t[0], ..., t[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= S <= 1.000.000.000
0 <= t[i] <= 1.000.000

SAMPLE INPUT 1:
3 10
1 2 5

SAMPLE OUTPUT 1:
11
(1 sesi mencakup pekerjaan 1 dan 2: 10 + (2-1)^2 = 11? Lalu pekerjaan 3: 10 + 0 = 10 -> total 21.
Atau 1 sesi besar untuk 1..3: 10 + (5-1)^2 = 10 + 16 = 26.
Atau 3 sesi terpisah: 10 + 10 + 10 = 30.
Jawaban terbaik: sesi [1, 2] dan [3]: 11 + 10 = 21.)

SAMPLE INPUT 2:
1 50
10

SAMPLE OUTPUT 2:
50
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll s;
    if (!(cin >> n >> s)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
