/*
============================================================
📋 TUGAS 8: Floor and Ceiling in Set
============================================================
Source: Original
Difficulty: Medium
Topics: set, lower_bound, upper_bound

PROBLEM:
Diberikan sebuah set bilangan awal, lalu Q query. Setiap query
berisi satu integer X. Untuk setiap query, output:
- Floor(X): elemen terbesar di set yang ≤ X (atau "NONE")
- Ceiling(X): elemen terkecil di set yang ≥ X (atau "NONE")

INPUT:
- Baris pertama: integer N (jumlah elemen set awal)
- Baris kedua: N integer (elemen set)
- Baris ketiga: integer Q (jumlah query)
- Q baris berikutnya: satu integer X per query

OUTPUT:
- Q baris: "floor ceiling" atau "NONE ceiling" atau "floor NONE" atau "NONE NONE"

CONSTRAINTS:
- 1 ≤ N, Q ≤ 200,000
- 1 ≤ elemen, X ≤ 1,000,000,000

SAMPLE INPUT:
5
1 3 5 7 9
4
4
5
0
10

SAMPLE OUTPUT:
3 5
5 5
NONE 1
9 NONE

NOTE: Floor(4)=3 (terbesar ≤ 4), Ceiling(4)=5 (terkecil ≥ 4)
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

    set<int> st;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        st.insert(x);
    }

    int l;
    cin >> l;
    while (l--)
    {
        int x;
        cin >> x;

        auto it_low = st.lower_bound(x);
        auto it_high = st.upper_bound(x);

        if (it_low == st.begin())
        {
            cout << "NONE" << " ";
        }
        else if (*it_low == x)
        {
            cout << x << " ";
        }
        else
        {
            it_low--;
            cout << *it_low << " ";
        }

        if (it_high == st.end())
        {
            cout << "NONE" << endl;
        }
        else if (*it_low == x)
        {
            cout << x << endl;
        }
        else
        {
            cout << *it_high << endl;
        }
    }

    return 0;
}
