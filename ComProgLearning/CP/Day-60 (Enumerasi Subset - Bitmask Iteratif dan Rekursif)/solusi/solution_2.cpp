/*
============================================================
  Solution 2: Cek Subset, Superset, dan Interseksi
============================================================
Pendekatan: Encode setiap himpunan sebagai bitmask, lalu gunakan
operasi bitwise untuk menjawab tiap query dalam O(1).

Kompleksitas: O(n + q) — O(n) encode, O(1) per query.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    int ka;
    cin >> ka;
    int A = 0;
    for (int i = 0; i < ka; i++)
    {
        int x;
        cin >> x;
        A |= (1 << x);
    }

    int kb;
    cin >> kb;
    int B = 0;
    for (int i = 0; i < kb; i++)
    {
        int x;
        cin >> x;
        B |= (1 << x);
    }

    while (q--)
    {
        string op;
        cin >> op;

        if (op == "IS_SUBSET")
        {
            cout << ((A & B) == A ? "YES" : "NO") << "\n";
        }
        else if (op == "IS_SUPERSET")
        {
            cout << ((A & B) == B ? "YES" : "NO") << "\n";
        }
        else if (op == "DISJOINT")
        {
            cout << ((A & B) == 0 ? "YES" : "NO") << "\n";
        }
        else if (op == "UNION")
        {
            cout << (A | B) << "\n";
        }
        else if (op == "INTERSECT")
        {
            cout << (A & B) << "\n";
        }
        else if (op == "DIFF")
        {
            cout << (A & ~B) << "\n";
        }
    }

    return 0;
}
