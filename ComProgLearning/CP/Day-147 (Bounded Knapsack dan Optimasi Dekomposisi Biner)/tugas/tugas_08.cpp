/*
============================================================
📋 TUGAS 08: Permainan Mesin Capit
============================================================
Source: Educational / Competitive Programming
Difficulty: Medium
Topics: Bounded Knapsack Dasar, Multi-Attribute

PROBLEM:
Di sebuah arena bermain arkade, terdapat mesin capit yang berisi boneka hadiah.
Setiap percobaan capit boneka jenis ke-i membutuhkan koin sebanyak w[i] keping,
memberikan kebahagiaan sebesar v[i] poin, dan mesin tersebut hanya berisi c[i] buah boneka jenis itu.
Pemain memiliki total K koin keping. Pemain boleh mencapit beberapa boneka jenis yang sama
selama stoknya masih tersedia di dalam mesin.
Tentukan total poin kebahagiaan maksimum yang bisa diperoleh.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: poin kebahagiaan maksimum.

CONSTRAINTS:
1 <= N <= 100
1 <= K <= 10.000
1 <= w[i] <= K
1 <= v[i] <= 10^9
1 <= c[i] <= 500

SAMPLE INPUT 1:
3 12
3 10 2
4 15 1
2 6 4

SAMPLE OUTPUT 1:
41
(Penjelasan: Ambil 2 boneka 0 (koin 6, poin 20) + 1 boneka 1 (koin 4, poin 15) + 1 boneka 2 (koin 2, poin 6) = total koin 12, total poin 41)
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

    vector<int> w(n);
    vector<ll> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack
    // vector<ll> dp(k + 1, 0)
    // Pecah c[i] secara biner dan lakukan loop mundur

    return 0;
}
