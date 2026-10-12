/*
============================================================
TEMPLATE Day 144 — Coin Change & Unbounded Knapsack
============================================================
Kumpulan fungsi template dan pola implementasi DP siap pakai
untuk masalah koin dan Unbounded Knapsack.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF_INT = 1e9 + 7;
const ll INF_LL = 1e18;
const int MOD = 1e9 + 7;

// ==========================================================
// 1. COIN CHANGE MINIMUM (Jumlah Koin Paling Sedikit)
// ==========================================================
// Menghitung jumlah koin minimum untuk membentuk tepat nominal x.
// Mengembalikan -1 jika nominal tidak mungkin dibentuk.
// Time: O(N * X) | Space: O(X)
int coinChangeMin(int x, const vector<int>& coins) {
    if (x == 0) return 0;
    vector<int> dp(x + 1, INF_INT);
    dp[0] = 0;

    for (int i = 1; i <= x; i++) {
        for (int c : coins) {
            if (i >= c && dp[i - c] != INF_INT) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }
    return (dp[x] == INF_INT ? -1 : dp[x]);
}

// ==========================================================
// 2. COIN CHANGE DENGAN REKONSTRUKSI SOLUSI
// ==========================================================
// Mengembalikan pair: {koin_minimum, daftar_koin_yang_dipakai}.
// Jika mustahil, koin_minimum bernilai -1 dan daftar koin kosong.
// Time: O(N * X) | Space: O(X)
pair<int, vector<int>> coinChangeWithReconstruct(int x, const vector<int>& coins) {
    if (x == 0) return {0, {}};
    vector<int> dp(x + 1, INF_INT);
    vector<int> pick(x + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= x; i++) {
        for (int c : coins) {
            if (i >= c && dp[i - c] != INF_INT) {
                if (dp[i - c] + 1 < dp[i]) {
                    dp[i] = dp[i - c] + 1;
                    pick[i] = c;
                }
            }
        }
    }

    if (dp[x] == INF_INT) return {-1, {}};

    vector<int> result;
    int curr = x;
    while (curr > 0) {
        int c = pick[curr];
        result.push_back(c);
        curr -= c;
    }
    return {dp[x], result};
}

// ==========================================================
// 3. UNBOUNDED KNAPSACK (Maksimum Nilai dengan Stok Bebas)
// ==========================================================
// Setiap barang ke-i memiliki bobot wt[i] dan nilai val[i].
// Barang boleh diambil berkali-kali tanpa batas.
// Time: O(N * W) | Space: O(W)
ll unboundedKnapsackMax(int W, const vector<int>& wt, const vector<ll>& val) {
    int n = wt.size();
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = wt[i]; w <= W; w++) { // LOOP MAJU: Unbounded
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

// ==========================================================
// 4. UNBOUNDED KNAPSACK MINIMUM COST (Biaya Minimum Target Tepat)
// ==========================================================
// Mencapai tepat kapasitas W dengan biaya total minimum.
// Time: O(N * W) | Space: O(W)
ll unboundedKnapsackMinCost(int W, const vector<int>& wt, const vector<ll>& cost) {
    int n = wt.size();
    vector<ll> dp(W + 1, INF_LL);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int w = wt[i]; w <= W; w++) {
            if (dp[w - wt[i]] != INF_LL) {
                dp[w] = min(dp[w], dp[w - wt[i]] + cost[i]);
            }
        }
    }
    return (dp[W] == INF_LL ? -1 : dp[W]);
}

// ==========================================================
// 4. COIN COMBINATIONS I (Permutasi — Urutan Berpengaruh)
// ==========================================================
// Banyak cara membentuk nominal x di mana urutan koin dibedakan.
// Pola: Loop nominal di LUAR, loop koin di DALAM.
// Time: O(N * X) | Space: O(X)
int coinCombinationsPermutations(int x, const vector<int>& coins, int mod = MOD) {
    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= x; i++) {
        for (int c : coins) {
            if (i >= c) {
                dp[i] = (dp[i] + dp[i - c]) % mod;
            }
        }
    }
    return dp[x];
}

// ==========================================================
// 5. COIN COMBINATIONS II (Kombinasi — Urutan Tidak Berpengaruh)
// ==========================================================
// Banyak cara membentuk nominal x di mana urutan koin diabaikan.
// Pola: Loop koin di LUAR, loop nominal di DALAM (MAJU).
// Time: O(N * X) | Space: O(X)
int coinCombinationsCombinations(int x, const vector<int>& coins, int mod = MOD) {
    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    for (int c : coins) {
        for (int i = c; i <= x; i++) { // LOOP MAJU: Unbounded
            dp[i] = (dp[i] + dp[i - c]) % mod;
        }
    }
    return dp[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Contoh penggunaan template
    int n, x;
    if (cin >> n >> x) {
        vector<int> coins(n);
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }

        cout << "Coin Change Min: " << coinChangeMin(x, coins) << "\n";
    }

    return 0;
}
