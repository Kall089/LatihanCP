/*
============================================================
✅ Solution 5: Coin Combinations II (Banyak Cara Kombinasi)
============================================================
Approach: Dynamic Programming 1D (Counting DP - Combination Order)
Complexity: Time O(N * X) | Space O(X)
Key Insight:
Pada soal di mana urutan koin TIDAK membedakan cara (kombinasi murni),
kita menempatkan loop KOIN di LUAR dan loop NOMINAL di DALAM.

Dengan memproses koin jenis ke-k setelah semua jenis koin sebelumnya selesai,
kita memastikan bahwa dalam setiap kombinasi yang terbentuk, koin selalu
muncul dalam urutan indeks yang tidak menurun (non-decreasing index).
Hal ini secara otomatis mengeliminasi duplikasi permutasi, seperti
{2, 3} dan {3, 2} yang hanya dihitung sekali.

Transisi:
Untuk setiap koin c:
  Untuk i dari c sampai X (loop MAJU agar koin c boleh dipakai berkali-kali):
    dp[i] = (dp[i] + dp[i - c]) % MOD

Base case:
dp[0] = 1 (nominal 0 dapat dibentuk oleh 1 kombinasi kosong).
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

    // Step 2: Loop koin di LUAR, loop nominal di DALAM (MAJU)
    for (int coin : c) {
        for (int i = coin; i <= x; i++) {
            dp[i] = (dp[i] + dp[i - coin]) % MOD;
        }
    }

    // Step 3: Output banyak kombinasi
    cout << dp[x] << "\n";

    return 0;
}
