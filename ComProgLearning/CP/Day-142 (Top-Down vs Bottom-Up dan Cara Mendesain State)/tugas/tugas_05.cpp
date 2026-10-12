/*
============================================================
📋 TUGAS 05: Liburan 4 Pilihan Aktivitas
============================================================
Source: Extension of AtCoder DP-C
Difficulty: Easy-Medium
Topics: State Design with Last Choice

PROBLEM:
Selama N hari liburan, kamu dapat memilih satu dari 4 aktivitas berbeda (0, 1, 2, atau 3)
setiap harinya.
Aktivitas j pada hari i memberikan kebahagiaan points[i][j].
Aturan: Kamu tidak boleh memilih aktivitas yang sama dua hari berturut-turut.
Hitung total kebahagiaan maksimum yang bisa kamu peroleh selama N hari.

INPUT FORMAT:
Baris pertama: N
N baris berikutnya: 4 bilangan bulat points[i][0], points[i][1], points[i][2], points[i][3]

OUTPUT FORMAT:
Satu bilangan bulat: total kebahagiaan maksimum.

CONSTRAINTS:
1 <= N <= 100.000
-1.000.000.000 <= points[i][j] <= 1.000.000.000

SAMPLE INPUT 1:
2
10 20 30 40
50 60 70 80

SAMPLE OUTPUT 1:
110
(Penjelasan: Hari 1 pilih aktivitas 3 (40). Hari 2 pilih aktivitas 2 (70). Total = 110.)

SAMPLE INPUT 2:
3
1 2 3 4
5 6 7 8
9 10 11 12

SAMPLE OUTPUT 2:
23
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> points(n, vector<long long>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) cin >> points[i][j];
    }

    // TODO: Implementasikan DP 2D dp[i][j] di mana j in {0, 1, 2, 3}
    // dp[i][j] = points[i][j] + max_{k != j} (dp[i-1][k])

    return 0;
}
