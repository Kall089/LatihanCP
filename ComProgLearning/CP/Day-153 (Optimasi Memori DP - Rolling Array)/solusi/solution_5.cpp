/*
============================================================
✅ Solution 5: Subsekuens Jumlah Target dengan Bitset (Subset Sum Bitset)
============================================================
Approach: Bitwise DP with std::bitset
Complexity: Time O(N * T / 64) | Space O(T / 8)
Key Insight:
1. Mengapa Bitset?
   Pada subset sum boolean biasa:
   dp[j] = dp[j] | dp[j - a[i]]
   Jika diimplementasikan dengan loop for biasa:
   for (int j = T; j >= a[i]; j--) dp[j] |= dp[j - a[i]];
   Ini membutuhkan N * T iterasi (1000 * 100000 = 10^8 operasi).

2. Operasi Bitwise 1 Baris:
   `dp |= (dp << a[i]);`
   Operator shift `<< a[i]` menggeser semua bit yang bernilai 1 ke kiri sejauh a[i].
   Bitwise OR `|=` menggabungkan kemungkinan lama dan kemungkinan baru.
   Karena bitset diimplementasikan menggunakan blok 64-bit integer (unsigned long long)
   di level perangkat keras, CPU memproses 64 state kapasitas dalam SATU instruksi mesin!
   Total operasi turun dari 10^8 menjadi ~1.5 x 10^6 operasi CPU.

3. Penghematan Memori Ekstrem:
   bitset<100005> hanya memerlukan:
   100005 / 8 = 12.500 byte ~ 12.2 KB memori!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_T = 100005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    bitset<MAX_T> dp;
    dp[0] = 1; // Base case: jumlah 0 selalu mungkin

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x <= t) {
            dp |= (dp << x);
        }
    }

    if (dp[t]) {
        cout << "BISA\n";
    } else {
        cout << "TIDAK BISA\n";
    }

    return 0;
}
