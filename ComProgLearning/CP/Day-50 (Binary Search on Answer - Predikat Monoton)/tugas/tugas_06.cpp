/*
============================================================
📋 Tugas 06: Minimum Time to Complete Trips (LeetCode 2187)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Waktu Minimal Total Trips)

PROBLEM STATEMENT:
Ada N bus di mana bus ke-i memerlukan waktu T[i] untuk menyelesaikan 1 perjalanan.
Setiap bus dapat melakukan perjalanan berulang kali secara independen dan bersamaan.
Cari waktu MINIMUM yang dibutuhkan agar seluruh bus secara total menyelesaikan minimal TOTAL_TRIPS perjalanan.

INPUT FORMAT:
- Baris 1: N TOTAL_TRIPS
- Baris 2: N integer T[1..N]

OUTPUT FORMAT:
- Satu integer: waktu minimum yang dibutuhkan.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1 ≤ TOTAL_TRIPS ≤ 10^7
- 1 ≤ T[i] ≤ 10^7

SAMPLE INPUT 1:
3 5
1 2 3

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
Pada t = 3:
- Bus 1 (waktu 1): 3 / 1 = 3 trips
- Bus 2 (waktu 2): 3 / 2 = 1 trip
- Bus 3 (waktu 3): 3 / 3 = 1 trip
Total trips = 3 + 1 + 1 = 5 trips.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long total_trips;
    if (!(cin >> n >> total_trips)) return 0;

    vector<long long> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];

    // TODO: Binary search pada waktu jawaban

    return 0;
}
