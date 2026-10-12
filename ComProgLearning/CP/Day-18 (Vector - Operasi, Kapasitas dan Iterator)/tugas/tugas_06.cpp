/*
============================================================
📋 TUGAS 6: Merge Two Sorted Vectors
============================================================
Source: Original
Difficulty: Medium
Topics: vector, two pointers, merge

PROBLEM:
Diberikan dua array yang SUDAH TERURUT (ascending).
Gabungkan keduanya menjadi satu array terurut.

INPUT:
- Baris pertama: integer N (ukuran array pertama)
- Baris kedua: N integer (array pertama, sorted)
- Baris ketiga: integer M (ukuran array kedua)
- Baris keempat: M integer (array kedua, sorted)

OUTPUT:
- Satu baris: N+M integer (array gabungan, sorted)

CONSTRAINTS:
- 1 ≤ N, M ≤ 200,000
- 1 ≤ a[i], b[i] ≤ 1,000,000,000

SAMPLE INPUT:
3
1 3 5
4
2 4 6 8

SAMPLE OUTPUT:
1 2 3 4 5 6 8

NOTE: Lakukan dalam O(N+M), BUKAN sort ulang O((N+M)log(N+M))
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

    vector<int> a(n);
    for (int &x : a)
    {
        cin >> x;
    }

    int m;
    cin >> m;
    vector<int> b(m);
    for (int &x : b)
    {
        cin >> x;
    }

    int i = 0, j = 0;

    vector<int> merged;

    while (i < n && j < m)
    {
        if (a[i] <= b[j])
        {
            merged.push_back(a[i]);
            i++;
        }
        else
        {
            merged.push_back(b[j]);
            j++;
        }
    }

    while (i < n)
    {
        merged.push_back(a[i]);
        i++;
    }

    while (j < m)
    {
        merged.push_back(b[j]);
        j++;
    }

    for (int x : merged)
    {
        cout << x << " ";
    }

    return 0;
}
