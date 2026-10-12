/*
============================================================
📋 TUGAS 2: Reverse Vector
============================================================
Source: Original
Difficulty: Easy
Topics: vector, reverse

PROBLEM:
Diberikan N bilangan. Cetak bilangan tersebut dalam urutan TERBALIK.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu baris: N bilangan dalam urutan terbalik (dipisah spasi)

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000

SAMPLE INPUT:
5
1 2 3 4 5

SAMPLE OUTPUT:
5 4 3 2 1
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

    for (long long &x : v)
    {
        cin >> x;
    }

    reverse(v.begin(), v.end());

    for (int x : v)
    {
        cout << x << " ";
    }

    return 0;
}
