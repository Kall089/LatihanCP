/*
============================================================
📋 TUGAS 1: Set Size After Insertions
============================================================
Source: Original
Difficulty: Easy
Topics: set, insert

PROBLEM:
Diberikan N bilangan. Setelah setiap insert ke set, cetak ukuran set.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- N integer (dipisah spasi): ukuran set setelah insert ke-1, ke-2, ..., ke-N

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
6
1 2 3 1 2 4

SAMPLE OUTPUT:
1 2 3 3 3 4

NOTE: Insert 1→size 1, insert 2→size 2, insert 3→size 3,
      insert 1 (sudah ada)→size 3, insert 2 (sudah ada)→size 3,
      insert 4→size 4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    int n;
    cin >> n;

    set<int> set;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        set.insert(x);
        cout << set.size() << " ";
    }

    return 0;
}
