/*
============================================================
📋 TUGAS 14: Journey
============================================================
Source: CF 721C
Difficulty: Hard
Topics: DP dua dimensi di DAG (maksimalkan jumlah simpul dengan batas waktu)

PROBLEM:
DAG N simpul, M edge berbobot waktu. Cari jalur 1 -> N yang melewati simpul
SEBANYAK mungkin dengan total waktu <= T. Cetak banyak simpul lalu rutenya.

INPUT FORMAT:
- Baris 1: N M T
- M baris: u v t

OUTPUT FORMAT:
- Baris 1: banyak simpul
- Baris 2: rutenya

CONSTRAINTS:
- 2 <= N <= 5000, 1 <= M <= 5000, 1 <= T <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 3 20                 4
1 2 5                  1 2 3 4
2 3 7
3 4 8
Penjelasan: total waktu 5+7+8 = 20, tepat sama dengan T, jadi diterima.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4 13                 3
1 2 5                  1 2 4
2 4 5
1 3 2
3 4 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1 1                  2
1 2 1                  1 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[v][k] = waktu MINIMUM mencapai v dengan tepat k simpul terlewati.
    // Jawaban: k terbesar dengan dp[N][k] <= T. Simpan par[v][k].
    // O(N*M) memori -> 25*10^6 int, perhatikan batas memori.
    return 0;
}
