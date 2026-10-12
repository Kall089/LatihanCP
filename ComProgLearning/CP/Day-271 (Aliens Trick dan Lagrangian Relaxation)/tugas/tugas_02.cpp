/*
============================================================
📋 TUGAS 02: Partisi Barisan dengan Faktor Pengali Bobot
============================================================
Source: Weighted K-Partition Optimization
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Diberikan array A[0], ..., A[N-1] berisi bilangan bulat non-negatif dan sebuah pengali M.
Bagi seluruh array menjadi TEPAT K buah subarray bersebelahan tidak kosong.
Biaya setiap subarray adalah M dikalikan kuadrat dari jumlah elemennya:
`Cost(Subarray) = M * (sum_{x in Subarray} x)^2`.

Tentukan TOTAL BIAYA MINIMUM dari partisi menjadi tepat K subarray!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan M.
Baris kedua berisi N bilangan bulat non-negatif A[0], ..., A[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
1 <= M <= 10.000
0 <= A[i] <= 10.000

SAMPLE INPUT 1:
3 2 3
1 2 3

SAMPLE OUTPUT 1:
54
(Biaya dasar = 18, dikalikan M = 3 -> 18 * 3 = 54)

SAMPLE INPUT 2:
4 2 2
1 1 1 1

SAMPLE OUTPUT 2:
16
(Biaya dasar = 8, dikalikan M = 2 -> 8 * 2 = 16)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll m;
    if (!(cin >> n >> k >> m)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
