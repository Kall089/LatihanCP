/*
============================================================
📋 TUGAS 7: Pair Frequency (Most Common Pair)
============================================================
Source: Original
Difficulty: Medium
Topics: vector, pair, sort, counting

PROBLEM:
Diberikan N pasangan bilangan (a, b). Cari pasangan yang PALING SERING
muncul dan berapa kali kemunculannya. Jika ada beberapa pasangan dengan
frekuensi sama, cetak yang paling KECIL secara lexicographic.

Pasangan (a,b) dan (a,b) dianggap SAMA. Tapi (a,b) ≠ (b,a).

INPUT:
- Baris pertama: integer N
- N baris berikutnya: dua integer a dan b

OUTPUT:
- Satu baris: a b count (pasangan paling sering + frekuensinya)

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a, b ≤ 1,000,000

SAMPLE INPUT:
6
1 2
3 4
1 2
3 4
1 2
5 6

SAMPLE OUTPUT:
1 2 3

SAMPLE INPUT 2:
4
2 1
1 2
2 1
1 2

SAMPLE OUTPUT 2:
1 2 2
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

    vector<pair<int, int>> v(n);

    for (auto &p : v)
    {
        cin >> p.first >> p.second;
    }

    sort(v.begin(), v.end());

    pair<int, int> best_pair = v[0];
    int best_count = 1;
    int cur_count = 1;

    for (int i = 1; i < n; i++)
    {
        if (v[i] == v[i - 1])
        {
            cur_count++;
        }
        else
        {
            if (cur_count > best_count)
            {
                best_count = cur_count;
                best_pair = v[i - 1];
            }
            cur_count = 1;
        }
    }

    if (cur_count > best_count)
    {
        best_count = cur_count;
        best_pair = v[n - 1];
    }

    cout << best_pair.first << " "
         << best_pair.second << " "
         << best_count;

    return 0;
}