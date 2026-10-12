/*
============================================================
📋 TUGAS 10: Penebangan Pohon Berjajar dengan Cooldown 2 Hari
============================================================
Source: House Robber Variation / Cooldown DP
Difficulty: Medium
Topics: DP 1D, Cooldown / Gap Constraint

PROBLEM:
Terdapat N pohon dalam satu baris dengan nilai kayu val[0], ..., val[N-1].
Jika kamu menebang pohon ke-i, kamu HARUS BERISTIRAHAT SELAMA 2 HARI BERIKUTNYA
(artinya pohon ke-i+1 dan pohon ke-i+2 TIDAK BOLEH ditebang).
Kamu baru boleh menebang lagi mulai pohon ke-i+3.
Tentukan NILAI MAKSIMUM kayu yang bisa kamu kumpulkan!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat val[0], ..., val[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: nilai maksimum kayu.

CONSTRAINTS:
1 <= N <= 100.000
0 <= val[i] <= 10^9

SAMPLE INPUT 1:
4
2 7 9 3

SAMPLE OUTPUT 1:
9
(Tebang pohon indeks 1 [nilai 7] atau indeks 2 [nilai 9]. Maksimum 9)

SAMPLE INPUT 2:
5
2 1 1 5 1

SAMPLE OUTPUT 2:
7
(Tebang pohon 0 [2] dan pohon 3 [5] -> jarak 3 pohon, valid, total 7)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan House Robber with 2-day gap dp[i] = max(dp[i-1], dp[i-3] + val[i])

    return 0;
}
