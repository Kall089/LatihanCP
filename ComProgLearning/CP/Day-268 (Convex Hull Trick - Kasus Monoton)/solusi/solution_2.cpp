/*
============================================================
✅ Solution 2: Katak dan Batu Berkabut (Frog 3 with CHT)
============================================================
Approach: Convex Hull Trick with Deque for Quadratic Transitions
Complexity: Time O(N) amortized | Space O(N)
Key Insight:
1. Aljabar Rekurensi:
   dp[i] = min_{j < i} (dp[j] + (h[i] - h[j])^2 + C)
         = h[i]^2 + C + min_{j < i} ( (-2 * h[j]) * h[i] + (dp[j] + h[j]^2) ).

2. Parameter Garis dan Kueri:
   Untuk setiap state j:
   - Kemiringan m_j = -2 * h[j]
   - Intersep b_j   = dp[j] + h[j]^2
   Untuk kueri i:
   - Titik evaluasi x = h[i]
   - Hasil akhir dp[i] = x^2 + C + query(x).

3. Monotonisitas:
   Karena h_0 <= h_1 <= ... <= h_{N-1}:
   - Kemiringan m = -2*h tidak menaik (menurun).
   - Kueri x = h tidak menurun (menaik).
   Syarat Lower Convex Hull Deque terpenuhi secara alami!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Line {
    ll m, b;
    ll eval(ll x) const {
        return m * x + b;
    }
};

struct ConvexHull {
    deque<Line> hull;

    static bool is_bad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(b.b - a.b) * (b.m - c.m) >= (__int128)(c.b - b.b) * (a.m - b.m);
    }

    void add_line(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b) return;
            hull.pop_back();
        }
        while (hull.size() >= 2 && is_bad(hull[hull.size() - 2], hull.back(), cur)) {
            hull.pop_back();
        }
        hull.push_back(cur);
    }

    ll query(ll x) {
        while (hull.size() >= 2 && hull[1].eval(x) <= hull[0].eval(x)) {
            hull.pop_front();
        }
        return hull[0].eval(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll c;
    if (!(cin >> n >> c)) return 0;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    ConvexHull ch;
    vector<ll> dp(n, 0);
    dp[0] = 0;
    ch.add_line(-2 * h[0], dp[0] + h[0] * h[0]);

    for (int i = 1; i < n; i++) {
        ll best = ch.query(h[i]);
        dp[i] = h[i] * h[i] + c + best;
        ch.add_line(-2 * h[i], dp[i] + h[i] * h[i]);
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
