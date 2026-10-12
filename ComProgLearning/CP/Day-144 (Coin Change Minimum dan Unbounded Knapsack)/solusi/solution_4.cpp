/*
============================================================
✅ Solution 4: Coin Combinations I (Banyak Cara Permutasi)
============================================================
Approach: Dynamic Programming 1D (Counting DP - Permutation Order)
Complexity: Time O(N * X) | Space O(X)
Key Insight:
Pada soal di mana URUTAN pemilihan koin membedakan cara (permutasi),
kita menempatkan loop nominal di LUAR dan loop koin di DALAM.

Artinya, saat menghitung nominal i, kita menganggap sembarang koin c (c <= i)
bisa menjadi koin terakhir yang ditempelkan pada kombinasi pembentuk (i - c).
Karena setiap transisi menempelkan koin di akhir urutan, urutan yang berbeda
secara otomatis terhitung sebagai jalur yang berbeda.

Transisi:
dp[i] = sum_{c in C, c <= i} (dp[i - c]) % MOD

Base case:
dp[0] = 1 (nominal 0 dibentuk oleh 1 cara: himpunan kosong).
dp[1...X] = 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // Step 1: Inisialisasi DP
    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    // Step 2: Loop nominal di LUAR, loop koin di DALAM
    for (int i = 1; i <= x; i++) {
        for (int coin : c) {
            if (i >= coin) {
                dp[i] = (dp[i] + dp[i - coin]) % MOD;
            }
        }
    }

    // Step 3: Output banyak cara
    cout << dp[x] << "\n";

    return 0;
}
