/*
============================================================
📋 TUGAS 10: Multiset — Dynamic Median
============================================================
Source: Classic
Difficulty: Medium
Topics: multiset, size, advance

PROBLEM:
Diberikan N bilangan satu per satu. Setelah SETIAP bilangan
dimasukkan, cetak MEDIAN dari semua bilangan yang sudah ada.

Median:
- Jika jumlah ganjil: elemen tengah
- Jika jumlah genap: elemen yang lebih kecil dari dua tengah

Contoh: [1,3,5] → median = 3
         [1,3,5,7] → median = 3 (lower middle)

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer (diberikan satu per satu)

OUTPUT:
- N integer (dipisah spasi): median setelah insert ke-1, ke-2, ..., ke-N

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
5 3 8 1 4

SAMPLE OUTPUT:
5 3 5 3 4

NOTE:
- Setelah [5]: median=5
- Setelah [3,5]: median=3 (lower middle)
- Setelah [3,5,8]: median=5
- Setelah [1,3,5,8]: median=3
- Setelah [1,3,4,5,8]: median=4
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

    multiset<int> ms;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        ms.insert(x);

        int pos = (ms.size() - 1) / 2;

        auto it = ms.begin();

        advance(it, pos);

        cout << *it << " ";
    }
    // Hint: Maintain multiset + iterator ke median.
    //       Saat insert, adjust iterator.

    return 0;
}
