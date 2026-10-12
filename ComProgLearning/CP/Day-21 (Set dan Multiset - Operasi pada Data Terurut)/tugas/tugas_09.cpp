/*
============================================================
📋 TUGAS 9: K Most Frequent Elements
============================================================
Source: LeetCode-style
Difficulty: Medium
Topics: map, sort by value, vector<pair>

PROBLEM:
Diberikan N bilangan dan integer K. Cari K elemen yang paling
SERING muncul. Output dalam urutan frekuensi MENURUN.
Jika frekuensi sama, output elemen yang LEBIH KECIL dulu.

INPUT:
- Baris pertama: dua integer N dan K
- Baris kedua: N buah integer

OUTPUT:
- Satu baris: K integer (K elemen paling sering)

CONSTRAINTS:
- 1 ≤ K ≤ jumlah elemen unik ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
8 2
1 1 1 2 2 3 3 3

SAMPLE OUTPUT:
1 3

SAMPLE INPUT 2:
6 3
1 2 2 3 3 3

SAMPLE OUTPUT 2:
3 2 1

NOTE: freq: {1:3, 2:2, 3:3}. K=2, top 2: freq 3 ada dua (1 dan 3).
      1 < 3, jadi output "1 3".
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<int, int> mp;

    // TODO: Kerjakan di sini
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        mp[x]++;
    }

    vector<pair<int, int>> vp(mp.begin(), mp.end());

    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.second != b.second)
        {
            return a.second > b.second;
        }
        return a.first < b.first;
    };
    sort(vp.begin(), vp.end(), cmp);

    for (int i = 0; i < m; i++)
    {
        cout << vp[i].first << " ";
    }
    return 0;
}
