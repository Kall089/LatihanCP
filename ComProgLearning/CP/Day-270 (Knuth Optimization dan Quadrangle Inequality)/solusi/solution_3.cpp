/*
============================================================
✅ Solution 3: Lampion dalam Lingkaran (Circular Knuth DP)
============================================================
Approach: Circular Array Doubling + Knuth Optimization
Complexity: Time O(N^2) | Space O(N^2)
Key Insight:
1. Konversi Melingkar ke Linier:
   Setiap konfigurasi penggabungan melingkar pada akhirnya memiliki satu sambungan
   yang dibuka terakhir, sehingga setara dengan penggabungan pada rantai linier
   dari jendela [l, l + n - 1] untuk suatu l in [0, n - 1].

2. Penggandaan Array (Array Doubling):
   Buat array baru berukuran 2N dengan menduplikasi array awal.
   Hitung prefix sum berukuran 2N + 1.

3. Knuth DP pada Rentang Terbatas (len <= N):
   Jalankan Knuth Optimization di atas tabel (2N) x (2N), tetapi
   hanya untuk panjang interval len dari 2 sampai N (bukan 2N).
   Jumlah operasi teleskopik untuk tabel (2N) x (2N) dengan batas len <= N
   tetap O(N^2).

4. Jawaban:
   Ambil minimum atas seluruh jendela linier: min_{0 <= l < n} dp[l][l + n - 1].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_circular_merge(int n, const vector<ll>& a) {
    if (n <= 1) return 0;

    int total_len = 2 * n;
    vector<ll> doubled(total_len);
    for (int i = 0; i < n; i++) {
        doubled[i] = a[i];
        doubled[i + n] = a[i];
    }

    vector<ll> pref(total_len + 1, 0);
    for (int i = 0; i < total_len; i++) {
        pref[i + 1] = pref[i] + doubled[i];
    }

    vector<vector<ll>> dp(total_len, vector<ll>(total_len, 0));
    vector<vector<int>> opt(total_len, vector<int>(total_len, 0));

    for (int i = 0; i < total_len; i++) {
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= total_len; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            int k_low  = opt[l][r - 1];
            int k_high = min(r - 1, opt[l + 1][r]);

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + (pref[r + 1] - pref[l]);
                if (cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }

    ll ans = INF;
    for (int l = 0; l < n; l++) {
        ans = min(ans, dp[l][l + n - 1]);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_circular_merge(n, a) << "\n";

    return 0;
}
