/*
============================================================
  Exercise 2: Deque sebagai Stack & Queue Sekaligus
============================================================
Implementasikan operasi campuran menggunakan deque.
Diberikan q operasi:
- PUSH_FRONT x  → tambah ke depan
- PUSH_BACK x   → tambah ke belakang
- POP_FRONT     → hapus dari depan
- POP_BACK      → hapus dari belakang
- FRONT / BACK  → lihat elemen depan/belakang
- SIZE          → cetak ukuran

📏 CONSTRAINTS:
  - 1 ≤ q ≤ 10^5

📎 SAMPLE INPUT:
  7
  PUSH_BACK 1
  PUSH_FRONT 2
  PUSH_BACK 3
  FRONT
  BACK
  POP_FRONT
  FRONT

📎 SAMPLE OUTPUT:
  2
  3
  1

💡 HINT: Gunakan deque<int> dengan operasi push_front, push_back, pop_front, pop_back.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    deque<int> dq;

    while (q--) {
        string op; cin >> op;

        if (op == "PUSH_FRONT" || op == "PUSH_BACK") {
            int x; cin >> x;
            // TODO: push ke deque
        } else if (op == "POP_FRONT") {
            // TODO: pop dari depan
        } else if (op == "POP_BACK") {
            // TODO: pop dari belakang
        } else if (op == "FRONT") {
            cout << dq.front() << "\n";
        } else if (op == "BACK") {
            cout << dq.back() << "\n";
        } else { // SIZE
            cout << dq.size() << "\n";
        }
    }
    return 0;
}
