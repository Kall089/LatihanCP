/*
============================================================
📋 Tugas 11: Minimize Max Distance to Gas Station (LeetCode 774)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search on Real Numbers (Double)

PROBLEM STATEMENT:
Ada N stasiun bensin di sepanjang jalan lurus pada posisi STATIONS[1..N].
Kamu boleh menambahkan K stasiun bensin baru di mana saja di antara stasiun awal.
Tujuanmu adalah MEMINIMALKAN JARAK MAKSIMUM antara dua stasiun bertetangga setelah menambah K stasiun baru.
Cetak hasil dengan presisi desimal minimal 4 angka di belakang koma.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N double STATIONS[1..N]

OUTPUT FORMAT:
- Satu double: jarak maksimum minimum (format fixed precision 4 desimal).

CONSTRAINTS:
- 2 ≤ N ≤ 10.000
- 1 ≤ K ≤ 10^6
- 0 ≤ STATIONS[i] ≤ 10^8

SAMPLE INPUT 1:
10 1
1 2 3 4 5 6 7 8 9 10

SAMPLE OUTPUT 1:
1.0000

HINT:
Gunakan 100 iterasi Binary Search pada double.
Fungsi check(dist) menghitung total stasiun tambahan ceil((STATIONS[i+1] - STATIONS[i]) / dist) - 1.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<double> st(n);
    for (int i = 0; i < n; i++) cin >> st[i];

    // TODO: Binary search pada double (100 iterasi)

    return 0;
}
