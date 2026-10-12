/*
============================================================
✅ Solution 6: Penjaga Museum Berjarak (House Robber O(1) Space)
============================================================
Approach: Constant Space DP (3-Variable Sliding Window)
Complexity: Time O(N) | Space O(1)
Key Insight:
1. Rekurens House Robber:
   Di setiap ruangan ke-i, pencuri memiliki 2 pilihan:
   - Tidak mencuri ruangan i: hasil terbaik sama dengan dp[i - 1].
   - Mencuri ruangan i: ia mendapatkan nilai a[i] ditambah hasil terbaik hingga dp[i - 2].
   Rumus: dp[i] = max(dp[i - 1], dp[i - 2] + a[i]).

2. Reduksi Menjadi O(1) Memori:
   Karena penghitungan dp[i] hanya memerlukan TEPAT dua state sebelumnya,
   kita tidak perlu menyimpan seluruh deretan nilai dp dari ruangan 0 hingga i - 3.
   Definisikan:
   - prev2 = nilai maksimum hingga dua ruangan sebelumnya (awalnya 0).
   - prev1 = nilai maksimum hingga satu ruangan sebelumnya (awalnya 0).
   Pada setiap kedatangan ruangan baru bernilai x:
     ll cur = max(prev1, prev2 + x);
     prev2 = prev1;
     prev1 = cur;

3. Streaming Input:
   Nilai setiap ruangan dibaca langsung dari cin tanpa dialokasikan ke dalam vector<ll>,
   menjadikan penggunaan memori program murni O(1) (~beberapa byte).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    ll prev2 = 0; // Mewakili dp[i - 2]
    ll prev1 = 0; // Mewakili dp[i - 1]

    for (int i = 0; i < n; i++) {
        ll val;
        cin >> val;

        ll cur = max(prev1, prev2 + val);
        prev2 = prev1;
        prev1 = cur;
    }

    cout << prev1 << "\n";

    return 0;
}
