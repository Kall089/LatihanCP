/*
============================================================
📋 TUGAS 15: Tiket Perjalanan Kereta (Minimum Cost Tickets)
============================================================
Source: LeetCode 983 / CSES Range Covering DP
Difficulty: Hard
Topics: Multi-day Pass Covering DP (Unbounded Passes)

PROBLEM:
Kamu merencanakan perjalanan kereta pada N hari tertentu sepanjang tahun.
Hari-hari perjalanan tersebut diberikan dalam sebuah array terurut menaik:
days[0], days[1], ..., days[N-1], di mana 1 <= days[i] <= 365.

Stasiun kereta menjual tiga jenis tiket perjalanan yang dapat dibeli berulang kali:
1. Tiket 1-hari: seharga costs[0] rupiah (berlaku untuk 1 hari).
2. Tiket 7-hari: seharga costs[1] rupiah (berlaku untuk 7 hari berturut-turut).
3. Tiket 30-hari: seharga costs[2] rupiah (berlaku untuk 30 hari berturut-turut).

Tiket memungkinkan kamu melakukan perjalanan tanpa batas pada hari-hari yang dicakupnya.
Tentukan total biaya minimum yang diperlukan untuk mencakup semua hari perjalananmu.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat days[0], ..., days[N-1].
Baris ketiga berisi tiga bilangan bulat costs[0], costs[1], costs[2].

OUTPUT FORMAT:
Satu bilangan bulat: biaya minimum tiket perjalanan.

CONSTRAINTS:
1 <= N <= 365
1 <= days[i] <= 365
days terurut tegas menaik
1 <= costs[0], costs[1], costs[2] <= 1.000

SAMPLE INPUT 1:
6
1 4 6 7 8 20
2 7 15

SAMPLE OUTPUT 1:
11
(Penjelasan: Beli tiket 7-hari pada hari 1 seharga 7 (mencakup hari 1, 4, 6, 7). Beli tiket 1-hari pada hari 8 seharga 2. Beli tiket 1-hari pada hari 20 seharga 2. Total biaya = 7 + 2 + 2 = 11)

SAMPLE INPUT 2:
12
1 2 3 4 5 6 7 8 9 10 30 31
2 7 15

SAMPLE OUTPUT 2:
17
(Penjelasan: Beli tiket 30-hari pada hari 1 seharga 15 (mencakup hari 1 s.d. 10 dan 30). Beli tiket 1-hari pada hari 31 seharga 2. Total = 15 + 2 = 17)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> days(n);
    for (int i = 0; i < n; i++) {
        cin >> days[i];
    }

    vector<int> costs(3);
    cin >> costs[0] >> costs[1] >> costs[2];

    // TODO: Selesaikan dengan DP 1D (Hari ke 1 s.d. 365)
    // dp[d] = biaya minimum mencakup perjalanan sampai hari ke-d.
    // Jika d bukan hari perjalanan, dp[d] = dp[d - 1].
    // Jika d adalah hari perjalanan:
    //   dp[d] = min({ dp[max(0, d - 1)] + costs[0],
    //                 dp[max(0, d - 7)] + costs[1],
    //                 dp[max(0, d - 30)] + costs[2] })

    return 0;
}
