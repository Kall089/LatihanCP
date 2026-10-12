/*
============================================================
📋 TUGAS 02: Banyaknya Posko Layanan (All K Group Costs)
============================================================
Source: Classic Post Office D&C DP
Difficulty: Medium
Topics: Divide and Conquer DP Optimization, All Layers Output

PROBLEM:
Terdapat N kampung pada satu garis lurus dengan posisi x[0] <= x[1] <= ... <= x[N-1].
Untuk setiap jumlah posko k dari 1 sampai K, hitung dan cetak biaya minimum pelayanan kampung
oleh TEPAT k posko wilayah!
Biaya satu wilayah adalah jumlah jarak seluruh kampung di wilayah tersebut ke median kampungnya.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1] (terurut menaik).

OUTPUT FORMAT:
Cetak K baris. Baris ke-k berisi biaya minimum untuk tepat k posko.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
0 <= x[i] <= 1.000.000

SAMPLE INPUT 1:
3 3
0 2 4

SAMPLE OUTPUT 1:
4
2
0

SAMPLE INPUT 2:
2 2
5 5

SAMPLE OUTPUT 2:
0
0
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

    // TODO: Selesaikan dengan D&C DP dan cetak biaya untuk tiap k = 1..K

    return 0;
}
