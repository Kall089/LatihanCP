/*
============================================================
📋 TUGAS 4: Find Min and Max
============================================================
Source: Original
Difficulty: Easy
Topics: vector, min_element, max_element

PROBLEM:
Diberikan N bilangan. Cetak elemen TERKECIL dan TERBESAR beserta
INDEX-nya (0-indexed). Jika ada beberapa, ambil index PERTAMA.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Baris pertama: min_value min_index
- Baris kedua: max_value max_index

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
6
3 1 4 1 5 9

SAMPLE OUTPUT:
1 1
9 5
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

    auto min = min_element(v.begin(), v.end());
    auto max = max_element(v.begin(), v.end());

    cout << *min << " " << (min - v.begin()) << endl;
    cout << *max << " " << (max - v.begin()) << endl;

    return 0;
}
