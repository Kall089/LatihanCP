/*
============================================================
✅ Solution 3: Rekonstruksi Koin Minimum
============================================================
Approach: Dynamic Programming 1D + Decision Tracking Array
Complexity: Time O(N * X) | Space O(X)
Key Insight:
Untuk merekonstruksi solusi tanpa menyimpan seluruh jalur pada setiap state,
kita hanya perlu mencatat SATU keputusan optimal: koin jenis apa yang
menyebabkan state dp[i] mencapai nilai minimumnya.

Array `pick[i]` menyimpan nilai koin c yang digunakan untuk mencapai nominal i.
Ketika nilai dp[i] diperbarui:
if (dp[i - c] + 1 < dp[i]) {
    dp[i] = dp[i - c] + 1;
    pick[i] = c;
}

Setelah tabel terisi:
Jika dp[X] != INF, kita mulai dari curr = X:
- Koin yang dipakai = pick[curr]
- Nominal sebelumnya = curr - pick[curr]
- Ulangi hingga curr == 0.
Panjang koin yang terkumpul dijamin tepat sama dengan dp[X].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // Step 1: Inisialisasi tabel DP dan array pick
    vector<int> dp(x + 1, INF);
    vector<int> pick(x + 1, -1);
    dp[0] = 0;

    // Step 2: Tabulasi dengan pencatatan keputusan
    for (int i = 1; i <= x; i++) {
        for (int coin : c) {
            if (i >= coin && dp[i - coin] != INF) {
                if (dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    pick[i] = coin;
                }
            }
        }
    }

    // Step 3: Pengecekan kemungkinan
    if (dp[x] == INF) {
        cout << -1 << "\n";
        return 0;
    }

    // Step 4: Rekonstruksi daftar koin
    cout << dp[x] << "\n";
    vector<int> result;
    int curr = x;
    while (curr > 0) {
        int coin = pick[curr];
        result.push_back(coin);
        curr -= coin;
    }

    // Cetak koin-koin penyusun
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << (i + 1 == result.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
