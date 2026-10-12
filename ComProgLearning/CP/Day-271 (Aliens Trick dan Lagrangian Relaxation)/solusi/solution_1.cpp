/*
============================================================
✅ Solution 1: Beli dan Jual Saham dengan Maksimal K Transaksi
============================================================
Approach: Aliens Trick (WQS Binary Search) + 1D State Machine DP
Complexity: Time O(N log(MaxPrice)) | Space O(1)
Key Insight:
1. Konkavitas Keuntungan f(k):
   Keuntungan maksimum f(k) dengan k transaksi adalah fungsi konkaf terhadap k.
   Hukum diminishing marginal returns berlaku karena transaksi paling menguntungkan
   akan selalu dieksekusi terlebih dahulu.

2. Lagrangian Relaxation:
   Setiap transaksi (pembelian & penjualan) dikenakan penalti biaya sebesar lambda.
   State DP:
   - free: {keuntungan, jumlah_transaksi} saat tidak memegang saham.
   - hold: {keuntungan, jumlah_transaksi} saat sedang memegang saham.
   Transisi untuk hari i:
   - new_free = max(free, {hold.val + P[i] - lambda, hold.cnt + 1})
   - new_hold = max(hold, {free.val - P[i], free.cnt})

3. WQS Binary Search:
   Jika lambda terlalu besar, DP memilih transaksi < K -> turunkan lambda.
   Jika lambda cukup kecil sehingga transaksi >= K -> catat lambda, coba naikkan lambda.
   Jawaban asli: free(lambda*).val + K * lambda*.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct State {
    ll val;
    int cnt;
    bool operator<(const State& o) const {
        if (val != o.val) return val < o.val;
        return cnt < o.cnt; // Pada kondisi seimbang (tie), prioritaskan jumlah transaksi terbanyak
    }
};

State run_dp(int n, const vector<ll>& p, ll lambda) {
    State free = {0, 0};
    State hold = {-p[0], 0};

    for (int i = 1; i < n; i++) {
        State next_free = max(free, State{hold.val + p[i] - lambda, hold.cnt + 1});
        State next_hold = max(hold, State{free.val - p[i], free.cnt});
        free = next_free;
        hold = next_hold;
    }
    return free;
}

ll solve_stock(int n, int k, const vector<ll>& p) {
    if (n <= 1 || k == 0) return 0;

    ll low = 0, high = 1e9 + 7;
    ll best_lambda = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        State res = run_dp(n, p, mid);
        if (res.cnt >= k) {
            best_lambda = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    State res = run_dp(n, p, best_lambda);
    return res.val + (ll)k * best_lambda;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    cout << solve_stock(n, k, p) << "\n";

    return 0;
}
