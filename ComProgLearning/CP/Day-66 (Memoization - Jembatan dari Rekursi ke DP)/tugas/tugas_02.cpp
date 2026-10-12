/*
============================================================
📋 TUGAS 02: Robot Pengurang (Reduce N to 1)
============================================================
Source: Classic DP / Top-Down Memoization
Difficulty: Easy-Medium
Topics: Top-Down Memoization, Optimization

PROBLEM:
Sebuah robot mulai pada bilangan bulat positif N dan ingin mengubahnya menjadi 1.
Dalam satu langkah operasi, robot dapat memilih salah satu aksi berikut:
1. Kurangi bilangan saat ini dengan 1: n -> n - 1
2. Jika bilangan genap (n % 2 == 0), bagi dengan 2: n -> n / 2
3. Jika bilangan habis dibagi 3 (n % 3 == 0), bagi dengan 3: n -> n / 3

Hitung JUMLAH LANGKAH OPERASI MINIMUM untuk mengubah N menjadi 1!
(Jika N = 1, robot sudah berada di 1, butuh 0 operasi).

INPUT FORMAT:
Satu baris berisi satu bilangan bulat N.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: langkah operasi minimum.

CONSTRAINTS:
1 <= N <= 100.000

SAMPLE INPUT 1:
10

SAMPLE OUTPUT 1:
3
(10 -> 9 [kurang 1] -> 3 [bagi 3] -> 1 [bagi 3], total 3 langkah)

SAMPLE INPUT 2:
1

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
