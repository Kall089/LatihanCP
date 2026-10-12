/*
============================================================
📋 TUGAS 12: House Robber Melingkar (House Robber II)
============================================================
Source: LeetCode 213
Difficulty: Medium
Topics: State Decomposition, Circular DP

PROBLEM:
Terdapat N rumah yang tersusun MELINGKAR di sekitar danau (artinya rumah ke-0 dan rumah ke-(N-1)
saling bertetangga!).
Setiap rumah memiliki uang sejumlah money[i].
Sistem alarm otomatis akan berbunyi jika DUA RUMAH YANG BERTETANGGA dirampok pada malam yang sama.
Hitung jumlah uang maksimum yang bisa dirampok tanpa memicu alarm.

INPUT FORMAT:
Baris pertama: N
Baris kedua: N bilangan bulat money[0], ..., money[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: total uang maksimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= money[i] <= 10.000

SAMPLE INPUT 1:
3
2 3 2

SAMPLE OUTPUT 1:
3
(Penjelasan: Kamu tidak bisa merampok rumah 0 dan rumah 2 karena keduanya bertetangga secara melingkar!)

SAMPLE INPUT 2:
4
1 2 3 1

SAMPLE OUTPUT 2:
4
(Penjelasan: Rampok rumah 1 (uang 2) dan rumah 3 (uang 1) = 3, ATAU rumah 0 (1) dan rumah 2 (3) = 4.)

SAMPLE INPUT 3:
1
99

SAMPLE OUTPUT 3:
99
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> money(n);
    for (int i = 0; i < n; i++) cin >> money[i];

    // TODO: Pecah masalah melingkar menjadi dua submasalah linear:
    // Kasus 1: Mengabaikan rumah pertama (rentang indeks 1 s.d. n-1)
    // Kasus 2: Mengabaikan rumah terakhir (rentang indeks 0 s.d. n-2)
    // Jawaban adalah max(Kasus 1, Kasus 2). Tangani n = 1 secara khusus!

    return 0;
}
