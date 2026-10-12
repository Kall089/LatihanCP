/*
============================================================
✅ Solution 3: Relai Pengiriman di Jalur Pantai (Classic Monotone DP CHT)
============================================================
Approach: Convex Hull Trick with Deque
Complexity: Time O(N) amortized | Space O(N)
Key Insight:
1. Rekurensi Murni:
   dp[i] = min_{j < i} (dp[j] + b[j] * a[i]).
   Basis: dp[0] = 0.

2. Identifikasi Garis:
   Setiap pos j yang sudah dihitung menyumbang garis:
   Line(m = b[j], c = dp[j]).

3. Kueri Monoton:
   Nilai a[i] tidak pernah menurun, dan b[j] tidak pernah menaik.
   Garis dengan slope menurun ditambahkan dari belakang.
   Kueri dengan nilai x menaik dibersihkan dari depan dengan pop_front().
   Total waktu: O(N) linier!
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
    if (!(cin >> n)) return 0;

    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    ConvexHull ch;
    ch.add_line(b[0], 0);

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans = ch.query(a[i]);
        ch.add_line(b[i], ans);
    }

    cout << ans << "\n";

    return 0;
}
