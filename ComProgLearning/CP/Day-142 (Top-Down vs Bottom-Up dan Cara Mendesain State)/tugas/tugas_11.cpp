/*
============================================================
📋 TUGAS 11: Lompat Katak Dua Kupon Sakti
============================================================
Source: Modification of Frog Jump
Difficulty: Medium
Topics: Multi-Dimensional State, Resource Management

PROBLEM:
Terdapat N batu dengan tinggi H[0], H[1], ..., H[N-1].
Dari batu i, kamu boleh melompat ke (i + 1) atau (i + 2) dengan biaya normal |H[i] - H[j]|.
Kali ini kamu memiliki TEPAT 2 KUPON GRATIS. Setiap kupon dapat digunakan untuk
menggratiskan satu kali lompatan (biaya menjadi 0).
Kamu boleh menggunakan 0, 1, atau 2 kupon sepanjang perjalanan dari batu 0 ke batu N-1.
Cari total energi minimum untuk mencapai batu N-1.

INPUT FORMAT:
Baris pertama: N
Baris kedua: N bilangan bulat H[0], ..., H[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: energi minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= H[i] <= 1.000.000.000

SAMPLE INPUT 1:
5
0 100 200 300 400

SAMPLE OUTPUT 1:
0
(Penjelasan: Lompat 0 -> 2 (kupon 1), lalu 2 -> 4 (kupon 2). Total biaya 0.)

SAMPLE INPUT 2:
4
0 10 20 100

SAMPLE OUTPUT 2:
10
(Penjelasan: Lompat 0 -> 1 normal (10), 1 -> 2 kupon (0), 2 -> 3 kupon (0). Total = 10.)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // TODO: Definisikan dp[i][used] di mana used in {0, 1, 2}
    // dp[i][used] = energi minimum ke batu i dengan used kupon sudah terpakai

    return 0;
}
