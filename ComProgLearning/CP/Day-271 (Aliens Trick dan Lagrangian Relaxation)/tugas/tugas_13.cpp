/*
============================================================
📋 TUGAS 13: Alokasi K Slot Waktu Drone Patroli Wilayah
============================================================
Source: Drone Patrol Slot Selection
Difficulty: Hard
Topics: Aliens Trick, Interval DP

PROBLEM:
Terdapat N slot misi patroli drone dengan waktu mulai L[i], waktu selesai R[i], dan skor prioritas P[i].
Satu unit drone armada hanya dapat menjalankan PALING BANYAK K misi yang tidak saling berbenturan (R[i] <= L[j]).

Tentukan TOTAL SKOR PRIORITAS MAKSIMUM yang dapat diselesaikan oleh drone!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
N baris berikutnya masing-masing berisi tiga bilangan bulat L[i], R[i], dan P[i].

OUTPUT FORMAT:
Satu baris berisi skor prioritas maksimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= L[i] < R[i] <= 1.000.000.000
1 <= P[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
0 4 100
3 7 150
5 9 120

SAMPLE OUTPUT 1:
220
(Misi 1 dan 3: 100 + 120 = 220, saling lepas (4 <= 5))

SAMPLE INPUT 2:
1 1
0 10 50

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

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Aliens Trick O(N log N)

    return 0;
}
