/*
============================================================
✅ Solution 4: Menutupi Titik dengan K Foto Kuadrat (IOI 2016 Aliens 1D)
============================================================
Approach: Aliens Trick (WQS Binary Search) + Monotonic CHT with Deque
Complexity: Time O(N log(MaxArea)) | Space O(N)
Key Insight:
1. Konveksitas Fungsi Luas f(k):
   Luas minimum foto f(k) dengan k foto kuadrat adalah fungsi konveks terhadap k.

2. Lagrangian Relaxation:
   Setiap foto baru dikenakan penalti lambda >= 0.
   dp[i] = min_{j < i} { dp[j] + (x[i] - x[j+1] + 1)^2 + lambda }
   Ekspansi aljabar:
   dp[i] = (x[i] + 1)^2 + lambda + min_{j < i} { -2*(x[i] + 1)*x[j+1] + dp[j] + x[j+1]^2 }
   - Gradien garis j: m = -2 * x[j+1] (menurun)
   - Evaluasi: q = x[i] + 1 (menaik)
   - Konstanta: c = dp[j] + x[j+1]^2

3. Monotonic CHT Deque O(1) amortized:
   Karena titik-titik x terurut menaik, CHT dapat dipelihara dengan Deque dalam O(1) amortized
   per transisi.

4. WQS Binary Search:
   Binary search lambda dalam [0, (x[N] - x[1] + 1)^2].
   Solusi: dp[N].val - K * lambda*.
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

DPRes run_dp(int n, const vector<ll>& x, ll lambda) {
    deque<Line> dq;
    dq.push_back({-2 * x[1], x[1] * x[1], 0});

    ll dp_val = 0;
    int dp_cnt = 0;

    for (int i = 1; i <= n; i++) {
        ll query_x = x[i] + 1;
        while (dq.size() >= 2) {
            ll v1 = dq[0].eval(query_x);
            ll v2 = dq[1].eval(query_x);
            if (v2 < v1 || (v2 == v1 && dq[1].cnt < dq[0].cnt)) {
                dq.pop_front();
            } else {
                break;
            }
        }

        dp_val = dq[0].eval(query_x) + query_x * query_x + lambda;
        dp_cnt = dq[0].cnt + 1;

        if (i < n) {
            Line new_line = {-2 * x[i + 1], dp_val + x[i + 1] * x[i + 1], dp_cnt};
            while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), new_line)) {
                dq.pop_back();
            }
            dq.push_back(new_line);
        }
    }

    return {dp_val, dp_cnt};
}

ll solve_photos(int n, int k, const vector<ll>& x_orig) {
    vector<ll> x(n + 1);
    for (int i = 0; i < n; i++) x[i + 1] = x_orig[i];

    ll max_span = x[n] - x[1] + 1;
    ll low = 0, high = max_span * max_span;
    ll best_lambda = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        DPRes res = run_dp(n, x, mid);
        if (res.cnt <= k) {
            best_lambda = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    DPRes res = run_dp(n, x, best_lambda);
    return res.val - (ll)k * best_lambda;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    cout << solve_photos(n, k, x) << "\n";

    return 0;
}
