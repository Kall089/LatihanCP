/*
============================================================
📋 TUGAS 6: Set Intersection
============================================================
Source: Original
Difficulty: Medium
Topics: set, find/count

PROBLEM:
Diberikan dua kumpulan bilangan. Cetak elemen yang ADA DI KEDUANYA
(intersection), sorted ascending.

INPUT:
- Baris pertama: integer N
- Baris kedua: N integer (elemen A, mungkin ada duplikat)
- Baris ketiga: integer M
- Baris keempat: M integer (elemen B, mungkin ada duplikat)

OUTPUT:
- Satu baris: elemen intersection (sorted, unique)
- Jika kosong, cetak "EMPTY"

CONSTRAINTS:
- 1 ≤ N, M ≤ 200,000
- 1 ≤ a[i], b[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
1 2 3 4 5
4
3 4 5 6

SAMPLE OUTPUT:
3 4 5

SAMPLE INPUT 2:
3
1 2 3
3
4 5 6

SAMPLE OUTPUT 2:
EMPTY
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

    set<int> v1;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        v1.insert(x);
    }

    int m;
    cin >> m;

    set<int> result;

    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        if (v1.count(x))
        {
            result.insert(x);
        }
    }

    if (result.empty())
    {
        cout << "EMPTY";
        return 0;
    }
    else
    {
        for (int x : result)
        {
            cout << x << " ";
        }
    }

    return 0;
}
