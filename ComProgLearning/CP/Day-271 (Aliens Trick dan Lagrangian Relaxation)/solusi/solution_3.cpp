/*
============================================================
✅ Solution 3: Memilih K Interval Berbobot Maksimum yang Saling Lepas
============================================================
Approach: Aliens Trick (WQS Binary Search) + Interval DP
Complexity: Time O(N log N + N log(MaxWeight)) | Space O(N)
Key Insight:
1. Konkavitas Keuntungan f(k):
   Keuntungan maksimum f(k) dengan k interval adalah fungsi konkaf terhadap k.

2. Prekomputasi Titik Potong Interval:
   Urutkan interval berdasarkan waktu selesai R[i].
   Untuk setiap interval i, cari interval terakhir prev[i] yang selesai sebelum atau pada waktu L[i]
   menggunakan upper_bound pada array nilai R. Dilakukan sekali diawal dalam O(N log N).

3. Evaluasi DP dengan Penalti Lambda:
   State DP: dp[i] = {keuntungan, jumlah_interval_terpilih}.
   Transisi O(1):
   - Opsi 1 (Lewati interval i): dp[i-1]
   - Opsi 2 (Pilih interval i): {dp[prev[i]].val + W[i] - lambda, dp[prev[i]].cnt + 1}
   dp[i] = max(Opsi 1, Opsi 2).

4. WQS Binary Search:
   Binary search lambda pada rentang [0, 2e14].
   Jawaban akhir: dp[N].val + K * lambda*.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Interval {
    ll l, r, w;
    bool operator<(const Interval& o) const {
        if (r != o.r) return r < o.r;
        return l < o.l;
    }
};

struct State {
    ll val;
    int cnt;
    bool operator<(const State& o) const {
        if (val != o.val) return val < o.val;
        return cnt < o.cnt; // Prioritaskan jumlah interval terbanyak saat tie
    }
};

State run_dp(int n, const vector<Interval>& iv, const vector<int>& prev_idx, ll lambda) {
    vector<State> dp(n + 1);
    dp[0] = {0, 0};

    for (int i = 1; i <= n; i++) {
        State opt_skip = dp[i - 1];
        int p = prev_idx[i];
        State opt_take = {dp[p].val + iv[i - 1].w - lambda, dp[p].cnt + 1};
        dp[i] = max(opt_skip, opt_take);
    }
    return dp[n];
}

ll solve_intervals(int n, int k, vector<Interval>& iv) {
    sort(iv.begin(), iv.end());

    vector<ll> ends(n);
    for (int i = 0; i < n; i++) ends[i] = iv[i].r;

    vector<int> prev_idx(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        auto it = upper_bound(ends.begin(), ends.begin() + i - 1, iv[i - 1].l);
        prev_idx[i] = (int)(it - ends.begin());
    }

    ll low = 0, high = 2e14;
    ll best_lambda = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        State res = run_dp(n, iv, prev_idx, mid);
        if (res.cnt >= k) {
            best_lambda = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    State res = run_dp(n, iv, prev_idx, best_lambda);
    return res.val + (ll)k * best_lambda;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<Interval> iv(n);
    for (int i = 0; i < n; i++) {
        cin >> iv[i].l >> iv[i].r >> iv[i].w;
    }

    cout << solve_intervals(n, k, iv) << "\n";

    return 0;
}
