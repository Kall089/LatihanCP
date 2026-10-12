/*
============================================================
📋 TUGAS 10: Memanjat Tangga dengan Biaya Minimum (Min Cost Climbing Stairs)
============================================================
Source: LeetCode 746 / Classic Top-Down
Difficulty: Easy-Medium
Topics: 1D Top-Down Memoization

PROBLEM:
Diberikan sebuah array cost berukuran N, di mana cost[i] adalah biaya yang harus dibayar saat
kamu berpijak pada anak tangga ke-i.
Setelah membayar biaya tangga ke-i, kamu dapat melangkah 1 tangga atau 2 tangga ke atas.
Kamu dapat memulai perjalanan dari anak tangga ke-0 atau anak tangga ke-1.
Tujuanmu adalah mencapai puncak tangga (anak tangga ke-N, di atas tangga terakhir).

Hitung BIAYA MINIMUM untuk mencapai puncak tangga!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat cost[0], ..., cost[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum mencapai puncak.

CONSTRAINTS:
2 <= N <= 100.000
0 <= cost[i] <= 1.000

SAMPLE INPUT 1:
3
10 15 20

SAMPLE OUTPUT 1:
15
(Mulai di tangga 1 [biaya 15], lalu melompat 2 langkah langsung ke puncak [indeks 3])

SAMPLE INPUT 2:
10
1 100 1 1 1 100 1 1 100 1

SAMPLE OUTPUT 2:
6
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> cost(n);
    for (int i = 0; i < n; i++) cin >> cost[i];

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
