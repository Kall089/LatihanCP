/*
============================================================
📋 Tugas 01: Koko Eating Bananas (LeetCode 875)
============================================================
Day: 50 | Difficulty: Easy/Medium
Topic: Binary Search on Answer (Minimalkan K)

PROBLEM STATEMENT:
Koko menyukai pisang. Ada N tumpukan pisang di mana tumpukan ke-i berisi PIL[i] pisang.
Penjaga akan kembali dalam H jam.
Koko dapat menentukan kecepatan makan K (pisang per jam). Setiap jam, Koko memilih satu tumpukan
dan memakan K pisang darinya. Jika tumpukan berisi kurang dari K pisang, Koko memakan seluruh isi
tumpukan tersebut dan TIDAK memakan tumpukan lain dalam jam yang sama.

Tentukan kecepatan makan MINIMUM K (integer) agar Koko bisa memakan semua pisang dalam waktu <= H jam.

INPUT FORMAT:
- Baris 1: N H
- Baris 2: N integer PIL[1], PIL[2], ..., PIL[N]

OUTPUT FORMAT:
- Satu integer: kecepatan minimum K.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- N ≤ H ≤ 10^9
- 1 ≤ PIL[i] ≤ 10^9

SAMPLE INPUT 1:
4 8
3 6 7 11

SAMPLE OUTPUT 1:
4

PENJELASAN SAMPLE 1:
Dengan K = 4:
- Tumpukan 1 (3 pisang): 1 jam
- Tumpukan 2 (6 pisang): 2 jam
- Tumpukan 3 (7 pisang): 2 jam
- Tumpukan 4 (11 pisang): 3 jam
Total jam = 1 + 2 + 2 + 3 = 8 jam (<= 8).

HINT:
Gunakan Binary Search pada K di range [1, max(PIL)].
Waktu untuk tumpukan i dengan kecepatan K adalah ceil(PIL[i] / K) = (PIL[i] + K - 1) / K.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long h;
    if (!(cin >> n >> h)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    // TODO: Implementasikan Binary Search on Answer untuk mencari K minimum

    return 0;
}
