/*
============================================================
✅ Solution 2: Unbounded Knapsack Maksimum Nilai
============================================================
Approach: Dynamic Programming 1D (Forward Loop Unbounded Knapsack)
Complexity: Time O(N * W) | Space O(W)
Key Insight:
Pada Unbounded Knapsack, setiap barang boleh diambil berkali-kali tanpa batas.
Dengan menggunakan loop MAJU untuk kapasitas w dari wt[i] hingga W, nilai
dp[w - wt[i]] yang diakses adalah nilai yang sudah memperhitungkan kemungkinan
penggunaan barang ke-i pada kapasitas yang lebih kecil.

Transisi:
dp[w] = max(dp[w], dp[w - wt[i]] + val[i])

Base case:
dp[0...W] = 0 (kapasitas 0 bernilai 0, inisialisasi semua kapasitas dengan 0).

Catatan tipe data:
Karena nilai barang v[i] dapat mencapai 10^9 dan dapat diambil berkali-kali,
gunakan `long long` untuk tabel DP guna mencegah integer overflow.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> wt(n);
    vector<ll> val(n);
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }

    // Step 1: Inisialisasi tabel DP dengan 0
    vector<ll> dp(W + 1, 0);

    // Step 2: Loop barang dan kapasitas MAJU (Forward loop)
    for (int i = 0; i < n; i++) {
        for (int w = wt[i]; w <= W; w++) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }

    // Step 3: Output nilai maksimum pada kapasitas W
    cout << dp[W] << "\n";

    return 0;
}
