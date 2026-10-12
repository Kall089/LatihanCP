/*
============================================================
📋 TUGAS 01: Ekspedisi Tepat K Stan
============================================================
Source: Review Synthesis / DP 3-Dimensi
Difficulty: Medium-Hard
Topics: DP 3D, House Robber Constraint, Exact Count K

PROBLEM:
Terdapat N stan festival berderet lurus. Stan ke-i memiliki biaya w[i] dan nilai v[i].
Kamu harus memilih TEPAT K STAN sedemikian sehingga:
1. Tidak ada dua stan yang bersebelahan langsung.
2. Total biaya tidak melebihi anggaran W.
3. Total nilai maksimum.
Jika mustahil memilih tepat K stan yang memenuhi syarat, cetak -1.

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, W, dan K.
N baris berikutnya berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Satu baris berisi nilai maksimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 60
0 <= W <= 500
0 <= K <= 30
1 <= w[i] <= 500
0 <= v[i] <= 10^9

SAMPLE INPUT 1:
3 2 2
1 5
1 100
1 5

SAMPLE OUTPUT 1:
10
(Pilih stan 1 dan 3, total biaya 2 <= 2, total nilai 5 + 5 = 10)

SAMPLE INPUT 2:
2 10 2
1 5
1 9

SAMPLE OUTPUT 2:
-1
(Hanya ada 2 stan dan keduanya bertetangga, mustahil memilih 2 stan)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W, K;
    if (!(cin >> n >> W >> K)) return 0;

    // TODO: Selesaikan DP 3D dp[i][k][w]

    return 0;
}
