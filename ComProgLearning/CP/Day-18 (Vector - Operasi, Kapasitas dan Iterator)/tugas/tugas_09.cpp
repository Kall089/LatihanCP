/*
============================================================
📋 TUGAS 9: Second Largest Element
============================================================
Source: Original
Difficulty: Medium
Topics: vector, sort/iteration

PROBLEM:
Diberikan N bilangan. Cari elemen TERBESAR KEDUA (distinct).
Jika semua elemen sama (tidak ada terbesar kedua), cetak "NO".

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu integer: elemen terbesar kedua, atau "NO"

CONSTRAINTS:
- 2 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
3 1 4 1 5

SAMPLE OUTPUT:
4

SAMPLE INPUT 2:
3
7 7 7

SAMPLE OUTPUT 2:
NO

NOTE: Terbesar kedua = elemen unik terbesar setelah yang tertinggi.
      [5, 5, 3, 1] → terbesar kedua = 3 (bukan 5!)
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

    vector<int> v(n);
    for (int &x : v)
    {
        cin >> x;
    }

    sort(v.begin(), v.end(), greater<int>());
    v.erase(unique(v.begin(), v.end()), v.end());

    if (v.size() < 2)
    {
        cout << "NO";
    }
    else
    {
        cout << v[1];
    }

    return 0;
}
