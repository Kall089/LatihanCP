/*
============================================================
✅ Solution 4: Rekonstruksi Solusi Bounded Knapsack
============================================================
Approach: Dekomposisi Biner + 2D DP Backtracking
Complexity: Time O(M * W) | Space O(M * W) di mana M = O(N * log C)
Key Insight:
Setelah memecah seluruh barang ber-stok menjadi daftar paket biner berindeks 0 s.d. M-1,
setiap paket diperlakukan sebagai barang 0/1 knapsack independen.

Dengan menyimpan tabel DP 2D `dp[i][w]` yang menyatakan nilai maksimum menggunakan
subset dari i paket pertama dengan kapasitas w:
- Tidak ambil paket ke-(i-1): `dp[i][w] = dp[i-1][w]`
- Ambil paket ke-(i-1) (jika w >= pkg.weight):
  `dp[i][w] = max(dp[i][w], dp[i-1][w - pkg.weight] + pkg.value)`

Rekonstruksi Solusi:
Mulai dari i = M dan w = W:
Jika `w >= pkg.weight` dan `dp[i][w] == dp[i-1][w - pkg.weight] + pkg.value`:
- Berarti paket ke-(i-1) diambil!
- Tambahkan `pkg.count` unit ke akumulator barang `ans[pkg.item_idx]`.
- Update `w -= pkg.weight`.
Jika tidak, lewati paket tersebut.
Decrement `i` hingga 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Package {
    int item_idx;
    int weight;
    ll value;
    int count;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // Step 1: Bentuk paket-paket biner
    vector<Package> pkgs;
    for (int i = 0; i < n; i++) {
        if (w[i] <= 0 || v[i] < 0 || c[i] <= 0 || W <= 0) continue;
        int c_eff = min(c[i], W / w[i]);

        int p = 1;
        while (c_eff > 0) {
            int q = min(p, c_eff);
            c_eff -= q;

            pkgs.push_back({i, q * w[i], (ll)q * v[i], q});
            p *= 2;
        }
    }

    int m = pkgs.size();

    // Step 2: Tabulasi 2D DP
    vector<vector<ll>> dp(m + 1, vector<ll>(W + 1, 0));

    for (int i = 1; i <= m; i++) {
        const auto& pkg = pkgs[i - 1];
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= pkg.weight) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - pkg.weight] + pkg.value);
            }
        }
    }

    // Nilai maksimum pada kapasitas W
    ll max_val = dp[m][W];
    cout << max_val << "\n";

    // Step 3: Backtracking untuk merekonstruksi kuantitas barang
    vector<int> ans(n, 0);
    int curr_w = W;
    for (int i = m; i >= 1; i--) {
        const auto& pkg = pkgs[i - 1];
        if (curr_w >= pkg.weight && dp[i][curr_w] == dp[i - 1][curr_w - pkg.weight] + pkg.value) {
            ans[pkg.item_idx] += pkg.count;
            curr_w -= pkg.weight;
        }
    }

    // Cetak kuantitas tiap jenis barang
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i + 1 == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
