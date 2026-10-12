/*
============================================================
✅ Solution 4: Akuisisi Lahan Persegi Panjang (Land Acquisition CHT)
============================================================
Approach: Dominance Pruning + Convex Hull Trick Deque
Complexity: Time O(N log N) for sorting + O(N) for CHT | Space O(N)
Key Insight:
1. Penyaringan Lahan Terdominasi:
   Jika w_a <= w_b dan h_a <= h_b, maka lahan a selalu bisa dimasukkan ke dalam paket yang
   berisi lahan b tanpa menambah dimensi maksimum sama sekali (biaya tidak bertambah).
   Setelah penyaringan, jika array diurutkan berdasarkan w menaik, maka h akan menurun ketat.

2. Transisi DP:
   dp[i] = min_{0 <= j < i} (dp[j] + h[j+1] * w[i]).
   - Slope m_j = h[j+1] (monoton menurun).
   - Titik kueri x_i = w[i] (monoton menaik).
   - Intersep c_j = dp[j].

3. Implementasi Deque:
   Karena slope menurun dan kueri x menaik, Lower Convex Hull dapat dipelihara dengan Deque dalam O(M).
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

struct Rect {
    ll w, h;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Rect> raw(n);
    for (int i = 0; i < n; i++) {
        cin >> raw[i].w >> raw[i].h;
    }

    // Urutkan berdasarkan w menaik, lalu h menaik
    sort(raw.begin(), raw.end(), [](const Rect& a, const Rect& b) {
        if (a.w != b.w) return a.w < b.w;
        return a.h < b.h;
    });

    // Singkirkan persegi panjang terdominasi menggunakan stack
    vector<Rect> filtered;
    for (int i = 0; i < n; i++) {
        while (!filtered.empty() && filtered.back().h <= raw[i].h) {
            filtered.pop_back();
        }
        filtered.push_back(raw[i]);
    }

    int m = filtered.size();
    // filtered berukuran m, 1-indexed untuk mempermudah:
    // filtered[i].w menaik ketat, filtered[i].h menurun ketat
    vector<ll> w(m + 1), h(m + 1);
    for (int i = 1; i <= m; i++) {
        w[i] = filtered[i - 1].w;
        h[i] = filtered[i - 1].h;
    }

    ConvexHull ch;
    vector<ll> dp(m + 1, 0);

    // Basis: garis dari j = 0 adalah slope h[1], intersep dp[0] = 0
    ch.add_line(h[1], 0);

    for (int i = 1; i <= m; i++) {
        dp[i] = ch.query(w[i]);
        if (i < m) {
            ch.add_line(h[i + 1], dp[i]);
        }
    }

    cout << dp[m] << "\n";

    return 0;
}
