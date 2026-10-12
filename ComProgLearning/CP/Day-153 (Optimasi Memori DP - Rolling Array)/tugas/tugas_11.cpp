/*
============================================================
📋 TUGAS 11: Partisi Himpunan Selisih Bobot Minimum
============================================================
Source: Classic DP / CSES Two Sets II Variation
Difficulty: Medium
Topics: Subset Sum, Bitset Optimization, Minimum Difference

PROBLEM:
Diberikan N buah bilangan bulat positif a[0], ..., a[N-1].
Bagi himpunan ini menjadi dua subset S1 dan S2 sehingga SELISIH MUTLAK antara jumlah elemen S1
dan jumlah elemen S2 bernilai SEKECIL MUNGKIN: |sum(S1) - sum(S2)| minimum.
Cetak selisih minimum tersebut!
Total jumlah elemen dapat mencapai 100.000, gunakan std::bitset untuk efisiensi.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: selisih minimum.

CONSTRAINTS:
1 <= N <= 500
Total jumlah elemen <= 100.000

SAMPLE INPUT 1:
4
1 6 11 5

SAMPLE OUTPUT 1:
1
(S1 = {1, 11} = 12, S2 = {6, 5} = 11, selisih |12 - 11| = 1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_SUM = 100005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    // TODO: Gunakan bitset untuk mencari subset sum terdekat ke total / 2

    return 0;
}
