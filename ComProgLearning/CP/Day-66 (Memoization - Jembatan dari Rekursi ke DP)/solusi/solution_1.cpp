/*
============================================================
✅ Solution 1: Lampion di Tangga Kampung (Climbing Stairs with Broken Steps)
============================================================
Approach: Top-Down Dynamic Programming with Memoization
Complexity: Time O(N + B) | Space O(N) for recursion call-stack and memo table
Key Insight:
1. Rekursi Alami:
   Untuk mencapai anak tangga ke-i, langkah terakhir yang mungkin adalah:
   - Melangkah 1 dari tangga i - 1
   - Melangkah 3 dari tangga i - 3
   Maka: f(i) = f(i - 1) + f(i - 3).

2. Tiga Baris Memoisasi:
   - Cek apakah state i sudah pernah dikunjungi: `if (seen[i]) return memo[i];`
   - Tandai telah dikunjungi: `seen[i] = true;`
   - Hitung, simpan, dan kembalikan: `return memo[i] = (f(i - 1) + f(i - 3)) % MOD;`

3. Kasus Khusus:
   - Jika tangga i rapuh (is_broken[i] == true), cara mencapai tangga tersebut adalah 0.
   - Karena 0 adalah nilai sah yang mungkin dihasilkan, menggunakan array penanda terpisah `seen`
     menjamin kita tidak menghitung ulang tangga yang memiliki 0 cara!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, b;
    if (!(cin >> n >> b)) return 0;

    vector<bool> broken(n + 1, false);
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        if (x <= n) broken[x] = true;
    }

    vector<ll> memo(n + 1, 0);
    vector<bool> seen(n + 1, false);

    // Fungsi rekursif top-down dengan memoisasi
    function<ll(int)> solve = [&](int i) -> ll {
        // Base case 1: di bawah tangga 0
        if (i < 0) return 0;

        // Base case 2: sampai di tangga 0
        if (i == 0) return 1;

        // Base case 3: tangga rapuh / rusak
        if (broken[i]) return 0;

        // Cek memo
        if (seen[i]) return memo[i];
        seen[i] = true;

        // Transisi: dari i - 1 dan i - 3
        ll ways = (solve(i - 1) + solve(i - 3)) % MOD;
        return memo[i] = ways;
    };

    cout << solve(n) << "\n";

    return 0;
}
