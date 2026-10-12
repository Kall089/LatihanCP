/*
============================================================
📋 TUGAS 09: Penggabungan Tumpukan Permen (Merge Stones Top-Down)
============================================================
Source: Classic Range DP / Top-Down Memoization
Difficulty: Medium-Hard
Topics: Interval Top-Down Memoization, Prefix Sums

PROBLEM:
Terdapat N tumpukan permen yang berjajar dalam satu baris. Tumpukan ke-i memiliki a[i] butir permen.
Dalam setiap langkah, kamu dapat menggabungkan DUA TUMPUKAN YANG BERSEBELAHAN menjadi satu tumpukan baru.
Biaya penggabungan adalah jumlah permen pada kedua tumpukan yang digabung.
Proses diulang sampai hanya tersisa 1 tumpukan tunggal.

Hitung TOTAL BIAYA PENGGABUNGAN MINIMUM yang mungkin dicapai!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI INTERVAL (Top-Down)!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 300
1 <= a[i] <= 1.000

SAMPLE INPUT 1:
3
1 2 3

SAMPLE OUTPUT 1:
9
(Gabung 1 & 2 [biaya 3, tumpukan jadi {3, 3}], lalu gabung 3 & 3 [biaya 6], total = 3 + 6 = 9)

SAMPLE INPUT 2:
4
3 2 4 1

SAMPLE OUTPUT 2:
20
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Selesaikan dengan top-down interval memoization: solve(l, r)

    return 0;
}
