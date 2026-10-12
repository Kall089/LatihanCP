/*
============================================================
📋 TUGAS 1: Sum of Vector
============================================================
Source: Original
Difficulty: Easy
Topics: vector, input, accumulate

PROBLEM:
Diberikan N bilangan bulat. Hitung jumlah (sum) semua elemen.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu integer: jumlah semua elemen

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- -1,000,000 ≤ a[i] ≤ 1,000,000

SAMPLE INPUT:
5
1 2 3 4 5

SAMPLE OUTPUT:
15

NOTE: Hati-hati overflow! Gunakan long long.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<long long> v(n);

    long long result = 0;

    for (long long &x : v)
    {
        cin >> x;
        result += x;
    }

    cout << result;

    return 0;
}
