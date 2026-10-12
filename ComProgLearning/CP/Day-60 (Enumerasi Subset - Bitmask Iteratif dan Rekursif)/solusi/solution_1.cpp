/*
============================================================
  Solution 1: Bit Operations Dasar
============================================================
Pendekatan: Implementasi langsung setiap operasi bitmask.
Semua operasi berjalan dalam O(1) menggunakan bitwise operators.

Kompleksitas: O(q) — satu operasi per query.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, q;
    cin >> N >> q;

    while (q--) {
        string op;
        cin >> op;

        if (op == "CHECK") {
            int i; cin >> i;
            cout << ((N >> i) & 1) << "\n";
        } else if (op == "SET") {
            int i; cin >> i;
            N |= (1 << i);
        } else if (op == "CLEAR") {
            int i; cin >> i;
            N &= ~(1 << i);
        } else if (op == "TOGGLE") {
            int i; cin >> i;
            N ^= (1 << i);
        } else if (op == "COUNT") {
            cout << __builtin_popcount(N) << "\n";
        } else if (op == "LOWBIT") {
            cout << (N == 0 ? 0 : N & -N) << "\n";
        } else if (op == "REMOVE") {
            if (N != 0) N &= (N - 1);
        }
    }

    cout << "(N akhir = " << N << ")\n";
    return 0;
}
