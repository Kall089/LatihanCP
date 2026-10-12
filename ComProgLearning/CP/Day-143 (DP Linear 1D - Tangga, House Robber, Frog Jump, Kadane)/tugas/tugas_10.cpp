/*
============================================================
📋 TUGAS 10: Best Time to Buy and Sell Stock with Cooldown
============================================================
Source: LC 309
Difficulty: Medium
Topics: DP 1D dengan tiga state

PROBLEM:
Harga saham per hari. Boleh membeli dan menjual berkali-kali, tetapi setelah
MENJUAL harus istirahat satu hari sebelum boleh membeli lagi. Cari keuntungan
maksimum.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N harga
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 5000, 0 <= harga <= 1000

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5                      3
1 2 3 0 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
1                      0
1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4                      6
1 4 2 7
Penjelasan: beli di hari 0 (harga 1), tahan, jual di hari 3 (harga 7) -> 6.
Alternatif beli-jual 1->4 lalu cooldown hanya memberi 3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> hold(n, 0);
    vector<int> rest(n, 0);
    vector<int> sold(n, 0);

    hold[0] = -a[0];
    rest[0] = 0;
    sold[0] = 0;

    for (int i = 1; i < n; i++)
    {
        hold[i] = max(hold[i - 1], rest[i - 1] - a[i]);

        sold[i] = hold[i - 1] + a[i];

        rest[i] = max(sold[i - 1], rest[i - 1]);
    }

    cout << max(sold[n - 1], rest[n - 1]);
}