/*
============================================================
📋 TUGAS 3: Most Frequent Element
============================================================
Source: Original
Difficulty: Easy
Topics: map, frequency, max

PROBLEM:
Diberikan N bilangan. Cari elemen yang paling SERING muncul.
Jika ada beberapa dengan frekuensi sama, output yang TERKECIL.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu integer: elemen paling sering (terkecil jika tie)

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
7
1 2 2 3 3 3 4

SAMPLE OUTPUT:
3

SAMPLE INPUT 2:
6
1 1 2 2 3 3

SAMPLE OUTPUT 2:
1
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

    map<int, int> freq;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        freq[x]++;
    }

    int best_val = INT_MAX;
    int best_freq = -1;
    for (auto &[val, freq] : freq)
    {
        if (freq > best_freq || (freq == best_freq && val < best_val))
        {
            best_val = val;
            best_freq = freq;
        }
    }

    cout << best_val << endl;

    return 0;
}
