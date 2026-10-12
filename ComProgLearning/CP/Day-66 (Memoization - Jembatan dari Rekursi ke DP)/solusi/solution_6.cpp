/*
============================================================
✅ Solution 6: Perkalian Potongan Angka Maksimum (Integer Break Top-Down)
============================================================
Approach: 1D Top-Down Dynamic Programming with Memoization
Complexity: Time O(N^2) | Space O(N)
Key Insight:
1. Rekursi Integer Break:
   Untuk memecah bilangan rem, kita bisa memilih potongan pertama sebesar i (1 <= i < rem).
   Sisa bilangan adalah (rem - i).
   Untuk sisa (rem - i), kita punya dua pilihan:
   - Tidak memecahnya lagi: kontribusinya adalah i * (rem - i).
   - Memecahnya lebih lanjut secara rekursif: kontribusinya adalah i * solve(rem - i).
   Maka:
   solve(rem) = max_{1 <= i < rem} (max(i * (rem - i), i * solve(rem - i))).

2. Memoisasi 1D:
   Array memo[N + 1] diinisialisasi dengan -1.
   Karena N <= 60, jumlah perkalian maksimum bisa mencapai ~3^20 = 3.48 x 10^9,
   sehingga tipe data `long long` wajib digunakan untuk mencegah integer overflow.
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

    vector<ll> memo(n + 1, -1);

    function<ll(int)> solve = [&](int rem) -> ll {
        // Base case
        if (rem <= 1) return 0;

        // Cek memo
        if (memo[rem] != -1) return memo[rem];

        ll best = 0;
        for (int i = 1; i < rem; i++) {
            ll opt1 = (ll)i * (rem - i);
            ll opt2 = (ll)i * solve(rem - i);
            best = max({best, opt1, opt2});
        }

        return memo[rem] = best;
    };

    cout << solve(n) << "\n";

    return 0;
}
