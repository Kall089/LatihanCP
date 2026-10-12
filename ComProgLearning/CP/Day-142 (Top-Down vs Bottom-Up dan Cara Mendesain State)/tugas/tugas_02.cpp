/*
============================================================
📋 TUGAS 02: Lompat Katak dengan Biaya Kuadrat
============================================================
Source: Codeforces / Original
Difficulty: Easy-Medium
Topics: DP 1D, Minimisasi Biaya

PROBLEM:
Terdapat N batu dengan tinggi H[0], H[1], ..., H[N-1].
Seekor katak berada di batu 0 dan ingin ke batu N-1.
Dari batu i, katak boleh melompat ke batu (i + 1) atau (i + 2).
Biaya energi yang dikeluarkan untuk melompat dari batu i ke batu j adalah (H[i] - H[j])^2.
Cari total biaya energi minimum untuk mencapai batu N-1.

INPUT FORMAT:
Baris pertama: N
Baris kedua: N bilangan bulat H[0], ..., H[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: total energi minimum.

CONSTRAINTS:
2 <= N <= 100.000
1 <= H[i] <= 10.000

SAMPLE INPUT 1:
4
1 4 2 8

SAMPLE OUTPUT 1:
22
(Penjelasan: 0 -> 2 -> 3: biaya (1-2)^2 + (2-8)^2 = 1 + 36 = 37.
 Atau 0 -> 1 -> 3: (1-4)^2 + (4-8)^2 = 9 + 16 = 25.
 Atau 0 -> 1 -> 2 -> 3: 9 + 4 + 36 = 49.
 Biaya minimum adalah 25? Cek 0 -> 1 -> 3 = 25.
 Tapi jika 0 -> 2 biaya 1, lalu 2 -> 3 biaya 36 -> total 37.
 Min = 25.)

SAMPLE INPUT 2:
2
10 5

SAMPLE OUTPUT 2:
25
(Penjelasan: (10-5)^2 = 25)
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

    // TODO: Implementasikan DP 1D dengan biaya kuadrat (h[i] - h[j])^2
    // Gunakan tipe data long long untuk mencegah overflow

    return 0;
}
