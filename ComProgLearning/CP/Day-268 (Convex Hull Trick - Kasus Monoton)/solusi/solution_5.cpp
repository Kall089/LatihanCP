/*
============================================================
✅ Solution 5: Penutup Jalan Berlubang (Covered Walkway CHT)
============================================================
Approach: Convex Hull Trick with Deque for Quadratic Partitioning
Complexity: Time O(N) | Space O(N)
Key Insight:
1. Rekurensi Kuadratik:
   dp[i] = min_{0 <= j < i} (dp[j] + C + (x[i] - x[j+1])^2)
         = x[i]^2 + C + min_{0 <= j < i} ( (-2 * x[j+1]) * x[i] + (dp[j] + x[j+1]^2) ).

2. Struktur Garis:
   Setiap pilihan pemisah j menyumbang garis:
   m_j = -2 * x[j+1]
   b_j = dp[j] + x[j+1]^2
   Query pada posisi x[i].

3. Karakteristik Monoton:
   Karena x terurut menaik, kemiringan m_j terurut menurun dan kueri x[i] terurut menaik.
   Deque mempertahankan amplop bawah dalam waktu linier O(N).
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

    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    ConvexHull ch;
    vector<ll> dp(n + 1, 0);

    // Basis: untuk j = 0, segmen mulai dari lubang 1
    ch.add_line(-2 * x[1], dp[0] + x[1] * x[1]);

    for (int i = 1; i <= n; i++) {
        ll best = ch.query(x[i]);
        dp[i] = x[i] * x[i] + c + best;

        if (i < n) {
            // j = i, segmen berikutnya mulai dari lubang i + 1
            ch.add_line(-2 * x[i + 1], dp[i] + x[i + 1] * x[i + 1]);
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
