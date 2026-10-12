/*
============================================================
✅ Solution 6: Partisi Barisan dengan Biaya Kuadratik dan Biaya Tetap Segmen
============================================================
Approach: Aliens Trick (WQS Binary Search) + Monotonic CHT with Deque
Complexity: Time O(N log(MaxCost)) | Space O(N)
Key Insight:
1. Invariansi Biaya Tetap:
   Karena partisi harus memiliki TEPAT K segmen, kontribusi dari biaya overhead tetap
   C_fixed ke total biaya selalu bernilai tepat K * C_fixed.
   Oleh karena itu, kita dapat menyelesaikan masalah tanpa C_fixed terlebih dahulu
   (kuadrat jumlah minimum), kemudian menambahkan K * C_fixed di akhir!

2. Monotonic CHT dengan Deque:
   Setiap segmen baru memiliki penalti lambda.
   dp[i] = pref[i]^2 + lambda + min_{j < i} { (-2 * pref[j]) * pref[i] + (dp[j] + pref[j]^2) }
   - Gradien garis j: m = -2 * pref[j] (menurun)
   - Evaluasi: x = pref[i] (menaik)
   - Konstanta: c = dp[j] + pref[j]^2

3. WQS Binary Search:
   Binary search lambda dalam [0, pref[N]^2].
   Solusi: dp[N].val - K * lambda* + K * C_fixed.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128_t int128;

struct Line {
    ll m, c;
    int cnt;
    ll eval(ll x) const {
        return m * x + c;
    }
};

bool bad(const Line& l1, const Line& l2, const Line& l3) {
    return (int128)(l2.c - l1.c) * (l2.m - l3.m) >= (int128)(l3.c - l2.c) * (l1.m - l2.m);
}

struct DPRes {
    ll val;
    int cnt;
};

DPRes run_dp(int n, const vector<ll>& pref, ll lambda) {
    deque<Line> dq;
    dq.push_back({0, 0, 0});

    ll dp_val = 0;
    int dp_cnt = 0;

    for (int i = 1; i <= n; i++) {
        ll x = pref[i];
        while (dq.size() >= 2) {
            ll v1 = dq[0].eval(x);
            ll v2 = dq[1].eval(x);
            if (v2 < v1 || (v2 == v1 && dq[1].cnt < dq[0].cnt)) {
                dq.pop_front();
            } else {
                break;
            }
        }

        dp_val = dq[0].eval(x) + x * x + lambda;
        dp_cnt = dq[0].cnt + 1;

        Line new_line = {-2 * pref[i], dp_val + pref[i] * pref[i], dp_cnt};
        while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), new_line)) {
            dq.pop_back();
        }
        dq.push_back(new_line);
    }

    return {dp_val, dp_cnt};
}

ll solve_k_squares_fixed(int n, int k, ll c_fixed, const vector<ll>& a) {
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    ll low = 0, high = pref[n] * pref[n];
    ll best_lambda = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        DPRes res = run_dp(n, pref, mid);
        if (res.cnt <= k) {
            best_lambda = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    DPRes res = run_dp(n, pref, best_lambda);
    ll base_ans = res.val - (ll)k * best_lambda;
    return base_ans + (ll)k * c_fixed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll c_fixed;
    if (!(cin >> n >> k >> c_fixed)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_k_squares_fixed(n, k, c_fixed, a) << "\n";

    return 0;
}
