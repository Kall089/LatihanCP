/*
============================================================
📋 TUGAS 11: Pemilihan K Periode Promosi Belanja Bebas Bentrok
============================================================
Source: Promotional Campaign Scheduling
Difficulty: Hard
Topics: Aliens Trick, Interval DP

PROBLEM:
Terdapat N tawaran kampanye promosi berurutan.
Kampanye ke-i dimulai pada hari L[i], berakhir pada hari R[i], dan mendatangkan omzet O[i].
Dua kampanye tidak boleh berjalan di hari yang sama (R[i] < L[j] atau R[j] < L[i]).
Platform hanya memiliki anggaran untuk menjalankan PALING BANYAK K kampanye.

Tentukan TOTAL OMZET MAKSIMUM yang dapat diraih!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
N baris berikutnya masing-masing berisi tiga bilangan bulat L[i], R[i], dan O[i].

OUTPUT FORMAT:
Satu baris berisi total omzet maksimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= L[i] <= R[i] <= 1.000.000.000
1 <= O[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
1 2 100
2 3 150
4 5 200

SAMPLE OUTPUT 1:
300
(Kampanye 1 dan 3: 100 + 200 = 300, karena hari 2 bentrok antara 1 dan 2)

SAMPLE INPUT 2:
1 1
1 10 500

SAMPLE OUTPUT 2:
500
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
