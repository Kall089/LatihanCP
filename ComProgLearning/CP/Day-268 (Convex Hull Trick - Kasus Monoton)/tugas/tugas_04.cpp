/*
============================================================
📋 TUGAS 04: Pemotongan Pohon Tercepat dengan Penggergajian
============================================================
Source: Classic CHT DP
Difficulty: Medium
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
Terdapat N pohon berurutan dari 1 sampai N. Pohon ke-i memiliki tinggi a[i] dan koefisien penggergajian b[i].
Diketahui a terurut tidak menurun (a[0] <= a[1] <= ... <= a[N-1]), dan b terurut tidak menaik (b[0] >= b[1] >= ... >= b[N-1]).
Pohon 1 sudah dipotong sejak awal dengan biaya 0.
Untuk memotong pohon i (i > 1), kita harus memakai gergaji dari pohon j yang sudah ditebang sebelumnya (j < i)
dengan biaya:
`dp[i] = min_{j < i} (dp[j] + b[j] * a[i])`.

Namun, kita juga harus membayar biaya pengangkutan kayu sebesar K untuk setiap pohon yang ditebang setelah pohon 1:
`dp[i] = min_{j < i} (dp[j] + b[j] * a[i] + K)`.

Tentukan biaya minimum untuk menebang pohon ke-N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].
Baris ketiga berisi N bilangan bulat b[0], ..., b[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
0 <= K <= 1.000.000.000
0 <= a[i], b[i] <= 1.000.000

SAMPLE INPUT 1:
3 10
1 2 3
5 3 1

SAMPLE OUTPUT 1:
25
(Tebang 1 -> 3 langsung: 0 + 5 * 3 + 10 = 25)

SAMPLE INPUT 2:
1 100
5
2

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
