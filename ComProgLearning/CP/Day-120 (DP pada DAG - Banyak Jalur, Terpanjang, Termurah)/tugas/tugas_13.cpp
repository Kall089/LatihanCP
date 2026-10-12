/*
============================================================
📋 TUGAS 13: DP dengan State Tambahan (K Kupon Diskon)
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: dp[v][k]

PROBLEM:
DAG berbobot. Kamu punya K kupon; setiap kupon menggratiskan biaya SATU edge.
Cari biaya minimum dari 1 ke N dengan memakai paling banyak K kupon.

INPUT FORMAT:
- Baris 1: N M K
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan, atau -1

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= K <= 10, 1 <= w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 2 1                  2
1 2 5
2 3 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 2 2                  0
1 2 5
2 3 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 2 0                  7
1 2 5
2 3 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[v][k] = biaya minimum ke v dengan k kupon TERPAKAI.
    // Relaksasi: dp[v][k] <- dp[u][k] + w   (bayar)
    //            dp[v][k+1] <- dp[u][k]     (pakai kupon)
    // Kompleksitas O((V+E)*K).
    return 0;
}
