/*
============================================================
✅ Solution 5: Penempatan K Stasiun Relai Sinyal (Aliens + CHT)
============================================================
Approach: Aliens Trick (WQS Binary Search) + Monotonic CHT with Deque
Complexity: Time O(N log(L^2)) | Space O(N)
Key Insight:
1. Konveksitas Distorsi f(k):
   Distorsi kuadratik f(k) dengan k lompatan adalah fungsi konveks terhadap k.

2. Lagrangian Relaxation:
   Setiap lompatan dikenakan penalti biaya lambda >= 0.
   dp[i] = min_{j < i} { dp[j] + (d[i] - d[j])^2 + lambda }
   dp[i] = d[i]^2 + lambda + min_{j < i} { (-2 * d[j]) * d[i] + (dp[j] + d[j]^2) }
   - Gradien garis j: m = -2 * d[j] (monoton menurun)
   - Evaluasi kueri: x = d[i] (monoton menaik)
   - Konstanta: c = dp[j] + d[j]^2

3. Monotonic CHT Deque O(1) amortized:
   Karena titik koordinat d[i] terurut menaik, CHT dapat dievaluasi dalam O(1) amortized.

4. WQS Binary Search:
   Binary search lambda dalam [0, d[N-1]^2].
   Solusi asli: dp[N-1].val - K * lambda*.
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

DPRes run_dp(int n, const vector<ll>& d, ll lambda) {
    deque<Line> dq;
    dq.push_back({-2 * d[0], d[0] * d[0], 0});

    ll dp_val = 0;
    int dp_cnt = 0;

    for (int i = 1; i < n; i++) {
        ll x = d[i];
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

        if (i < n - 1) {
            Line new_line = {-2 * d[i], dp_val + d[i] * d[i], dp_cnt};
            while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), new_line)) {
                dq.pop_back();
            }
            dq.push_back(new_line);
        }
    }

    return {dp_val, dp_cnt};
}

ll solve_relays(int n, int k, const vector<ll>& d) {
    ll low = 0, high = d[n - 1] * d[n - 1];
    ll best_lambda = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        DPRes res = run_dp(n, d, mid);
        if (res.cnt <= k) {
            best_lambda = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    DPRes res = run_dp(n, d, best_lambda);
    return res.val - (ll)k * best_lambda;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    cout << solve_relays(n, k, d) << "\n";

    return 0;
}
