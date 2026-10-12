/*
============================================================
TEMPLATE Day 142 — Top-Down, Bottom-Up & Desain State
============================================================
Kumpulan template dan pola implementasi DP siap pakai.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const ll MOD = 1000000007LL;

// ==========================================================
// 1. TOP-DOWN (MEMOIZATION) BOILERPLATE
// ==========================================================
// Gunakan penanda 'visited' jika jawaban sah dari fungsi bisa bernilai -1
// untuk menghindari sentinel collision yang menyebabkan TLE.

const int MAXN = 100005;
ll memo[MAXN];
bool visited[MAXN];

void resetTopDown(int n) {
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
        visited[i] = false;
    }
}

ll solveTopDown(int i, const vector<ll>& a) {
    // 1. Base Case
    if (i <= 0) return 0;

    // 2. Cek Cache
    if (visited[i]) return memo[i];
    visited[i] = true;

    // 3. Transisi / Rekurens
    ll res = solveTopDown(i - 1, a) + a[i];
    if (i >= 2) {
        res = min(res, solveTopDown(i - 2, a) + a[i]);
    }

    // 4. Simpan ke Cache & Return
    return memo[i] = res;
}

// ==========================================================
// 2. BOTTOM-UP (TABULATION) BOILERPLATE
// ==========================================================
// Menghindari rekursi dan bahaya stack overflow untuk N > 10^5.

ll solveBottomUp(int n, const vector<ll>& h) {
    if (n <= 1) return 0;

    vector<ll> dp(n, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == INF) continue;

        // Forward (Push) Transitions
        if (i + 1 < n) {
            dp[i + 1] = min(dp[i + 1], dp[i] + abs(h[i + 1] - h[i]));
        }
        if (i + 2 < n) {
            dp[i + 2] = min(dp[i + 2], dp[i] + abs(h[i + 2] - h[i]));
        }
    }

    return dp[n - 1];
}

// ==========================================================
// 3. ROLLING ARRAY (SPACE OPTIMIZATION)
// ==========================================================
// Mereduksi memori dari O(N) menjadi O(1) ketika dp[i] hanya
// bergantung pada dp[i-1] dan dp[i-2].

ll solveRollingArray(int n, const vector<ll>& h) {
    if (n <= 1) return 0;

    ll prev2 = 0;                        // dp[0]
    ll prev1 = abs(h[1] - h[0]);         // dp[1]

    for (int i = 2; i < n; i++) {
        ll cur = min(prev1 + abs(h[i] - h[i - 1]),
                     prev2 + abs(h[i] - h[i - 2]));
        prev2 = prev1;
        prev1 = cur;
    }

    return prev1;
}

// ==========================================================
// 4. MULTI-DIMENSIONAL STATE (COUPON / RESOURCE PATTERN)
// ==========================================================
// dp[i][used]: biaya minimum ke pos i dengan status kupon (0/1)

ll solveCouponDP(int n, const vector<ll>& h) {
    if (n <= 1) return 0;

    vector<vector<ll>> dp(n, vector<ll>(2, INF));
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 0; i < n; i++) {
        for (int next_pos : {i + 1, i + 2}) {
            if (next_pos >= n) continue;
            ll cost = abs(h[next_pos] - h[i]);

            // Tanpa pakai kupon
            if (dp[i][0] < INF) dp[next_pos][0] = min(dp[next_pos][0], dp[i][0] + cost);
            if (dp[i][1] < INF) dp[next_pos][1] = min(dp[next_pos][1], dp[i][1] + cost);

            // Pakai kupon saat ini
            if (dp[i][0] < INF) dp[next_pos][1] = min(dp[next_pos][1], dp[i][0] + 0LL);
        }
    }

    return min(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Silakan panggil template fungsi yang sesuai dengan kebutuhan soal!
    return 0;
}
