/*
============================================================
📦 TEMPLATE BOILERPLATE: Divide and Conquer DP Optimization
============================================================
Day: 267 | Topic: Divide and Conquer DP Optimization
Standard: C++17 Competitive Programming Master Template

Digunakan untuk menyelesaikan formulasi rekurensi:
dp[g][i] = min_{0 <= j < i} { dp[g-1][j] + Cost(j + 1, i) }
dengan syarat titik potong optimal opt[g][i] monoton tidak menurun terhadap i.

Modul yang tersedia:
1. `dnc_dp_standard`: Optimasi D&C DP standar dengan fungsi biaya Cost(l, r) berbiaya O(1).
2. `dnc_dp_two_pointers`: Optimasi D&C DP dengan jendela geser Stateful Two Pointers (Mo-Style)
   ketika Cost(l, r) tidak dapat dievaluasi dalam O(1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// ============================================================
// 1. Template D&C DP Standar (Cost O(1))
// ============================================================
// Kompleksitas: Waktu O(K * N log N), Memori O(N)
template <typename CostFunc>
vector<ll> dnc_dp_standard(int n, int k, CostFunc cost) {
    vector<ll> dp_prev(n + 1, INF);
    vector<ll> dp_curr(n + 1, INF);
    dp_prev[0] = 0;

    for (int g = 1; g <= k; g++) {
        fill(dp_curr.begin(), dp_curr.end(), INF);

        function<void(int, int, int, int)> compute = [&](int l, int r, int opt_l, int opt_r) {
            if (l > r) return;

            int mid = l + (r - l) / 2;
            int best_j = opt_l;
            ll best_val = INF;

            for (int j = opt_l; j <= min(opt_r, mid - 1); j++) {
                if (dp_prev[j] == INF) continue;
                ll cand = dp_prev[j] + cost(j + 1, mid);
                if (cand < best_val) {
                    best_val = cand;
                    best_j = j;
                }
            }

            dp_curr[mid] = best_val;

            // Divide & Conquer
            compute(l, mid - 1, opt_l, best_j);
            compute(mid + 1, r, best_j, opt_r);
        };

        compute(g, n, g - 1, n - 1);
        dp_prev = dp_curr;
    }

    return dp_prev; // dp_prev[n] adalah jawaban minimum
}

// ============================================================
// 2. Template D&C DP dengan Stateful Two-Pointers (Mo-Style)
// ============================================================
// Cocok untuk penghitungan inversi atau pasangan kembar
struct TwoPointerCost {
    int cur_l = 1, cur_r = 0;
    ll cur_cost = 0;
    vector<int> cnt;
    const vector<int>& a;

    TwoPointerCost(int n, const vector<int>& arr) : cnt(n + 1, 0), a(arr) {}

    void add(int idx) {
        cur_cost += cnt[a[idx]];
        cnt[a[idx]]++;
    }

    void remove(int idx) {
        cnt[a[idx]]--;
        cur_cost -= cnt[a[idx]];
    }

    ll get(int l, int r) {
        while (cur_r < r) add(++cur_r);
        while (cur_l > l) add(--cur_l);
        while (cur_r > r) remove(cur_r--);
        while (cur_l < l) remove(cur_l++);
        return cur_cost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TEMPLATE DIVIDE AND CONQUER DP OPTIMIZATION ===\n";
    cout << "Modul 1: dnc_dp_standard (Cost O(1))\n";
    cout << "Modul 2: dnc_dp_two_pointers (Mo-Style Window)\n";

    return 0;
}
