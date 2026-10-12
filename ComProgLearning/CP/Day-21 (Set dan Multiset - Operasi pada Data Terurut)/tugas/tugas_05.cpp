/*
============================================================
📋 TUGAS 5: Map — Inventory System
============================================================
Source: Original
Difficulty: Easy
Topics: map, insert/update/query

PROBLEM:
Implementasi sistem inventory sederhana. Ada Q operasi:
- "add item qty": tambah qty ke item (buat baru jika belum ada)
- "remove item qty": kurangi qty dari item (jika qty ≤ 0, hapus item)
- "query item": cetak qty item saat ini (0 jika tidak ada)

INPUT:
- Baris pertama: integer Q
- Q baris berikutnya: operasi sesuai format di atas

OUTPUT:
- Untuk setiap "query": cetak qty (satu per baris)

CONSTRAINTS:
- 1 ≤ Q ≤ 200,000
- 1 ≤ |item| ≤ 20
- 1 ≤ qty ≤ 1,000,000

SAMPLE INPUT:
7
add apple 5
add banana 3
query apple
remove apple 2
query apple
remove apple 10
query apple

SAMPLE OUTPUT:
5
3
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<string, int> inv;

    int n;
    cin >> n;

    while (n--)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "add")
        {
            string item;
            int count;
            cin >> item >> count;
            inv[item] += count;
        }
        else if (cmd == "remove")
        {
            string item;
            int count;
            cin >> item >> count;
            inv[item] -= count;
            if (inv[item] <= 0)
            {
                inv.erase(item);
            }
        }
        else
        {
            string item;
            cin >> item;
            cout << inv[item];
        }
    }

    return 0;
}
