/*
============================================================
✅ Solution 5: Jual Beli Saham dengan Cooldown (State Machine DP)
============================================================
Approach: Dynamic Programming FSM (Finite State Machine)
Complexity: Time O(N) | Space O(1)

Key Insight:
Pada akhir setiap hari i, posisi kita selalu berada pada salah satu dari 3 status:
1. HOLD: Memegang saham.
   Bisa karena kemarin sudah memegang saham (hold[i-1]), atau kemarin rest lalu hari ini beli (rest[i-1] - price[i]).
   hold[i] = max(hold[i-1], rest[i-1] - price[i])

2. SOLD: Baru saja menjual saham hari ini.
   Hanya bisa terjadi jika kemarin sedang memegang saham, lalu hari ini dijual dengan harga price[i].
   sold[i] = hold[i-1] + price[i]

3. REST: Sedang tidak memegang saham dan tidak menjual hari ini (bisa hari biasa atau hari cooldown).
   Bisa karena kemarin sudah rest (rest[i-1]), atau kemarin baru saja sold (sold[i-1] menjadi rest hari ini).
   rest[i] = max(rest[i-1], sold[i-1])

Basis (Hari 0):
hold = -price[0]
sold = 0
rest = 0

Jawaban akhir:
max(sold, rest) (tidak mungkin optimal mengakhiri periode dengan masih memegang saham yang belum dijual).

Sample 1:
Input:
5
1 2 3 0 2
Output:
3

Sample 2:
Input:
1
1
Output:
0

Sample 3:
Input:
5
7 6 4 3 1
Output:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    int hold = -price[0];
    int sold = 0;
    int rest = 0;

    for (int i = 1; i < n; i++) {
        int prev_hold = hold;
        int prev_sold = sold;
        int prev_rest = rest;

        hold = max(prev_hold, prev_rest - price[i]);
        sold = prev_hold + price[i];
        rest = max(prev_rest, prev_sold);
    }

    cout << max(sold, rest) << "\n";

    return 0;
}
