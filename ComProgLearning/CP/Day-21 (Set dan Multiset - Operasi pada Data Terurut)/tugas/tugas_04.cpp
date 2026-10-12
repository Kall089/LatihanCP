/*
============================================================
📋 TUGAS 4: Set Operations (Union)
============================================================
Source: Original
Difficulty: Easy
Topics: set, insert from multiple sources

PROBLEM:
Diberikan dua kumpulan bilangan (set A dan set B).
Cetak UNION dari keduanya (semua elemen unik dari A dan B, sorted).

INPUT:
- Baris pertama: integer N (jumlah elemen A)
- Baris kedua: N integer (elemen A)
- Baris ketiga: integer M (jumlah elemen B)
- Baris keempat: M integer (elemen B)

OUTPUT:
- Satu baris: semua elemen union, sorted ascending

CONSTRAINTS:
- 1 ≤ N, M ≤ 200,000
- 1 ≤ a[i], b[i] ≤ 1,000,000,000

SAMPLE INPUT:
4
1 3 5 7
3
2 3 6

SAMPLE OUTPUT:
1 2 3 5 6 7
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<int> v;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        v.insert(x);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        v.insert(x);
    }

    for (int x : v)
    {
        cout << x << " ";
    }

    return 0;
}
