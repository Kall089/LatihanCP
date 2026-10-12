/*
============================================================
📦 TEMPLATE BOILERPLATE: Convex Hull Trick (Kasus Monoton)
============================================================
Day: 268 | Topic: Convex Hull Trick (Monotone Lines and Queries)
Standard: C++17 Competitive Programming Master Template

Digunakan untuk optimasi DP linier:
dp[i] = min_{j < i} { dp[j] + b[j] * a[i] }
atau
dp[i] = max_{j < i} { dp[j] + b[j] * a[i] }

Modul yang tersedia:
1. `MinConvexHull`: Deque O(1) amortized untuk MINIMASI (slope menurun, query menaik).
2. `MaxConvexHull`: Deque O(1) amortized untuk MAKSIMASI (slope menaik, query menaik).
3. `MinConvexHullBS`: Vector O(log N) untuk MINIMASI jika query x tidak monoton.
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

// ============================================================
// 1. MinConvexHull (Lower Hull, Slope Menurun, Query x Menaik)
// ============================================================
// Kompleksitas: O(1) amortized per insert & query
struct MinConvexHull {
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

// ============================================================
// 2. MaxConvexHull (Upper Hull, Slope Menaik, Query x Menaik)
// ============================================================
// Kompleksitas: O(1) amortized per insert & query
struct MaxConvexHull {
    deque<Line> hull;

    static bool is_bad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(a.b - b.b) * (c.m - b.m) >= (__int128)(b.b - c.b) * (b.m - a.m);
    }

    void add_line(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b >= b) return;
            hull.pop_back();
        }
        while (hull.size() >= 2 && is_bad(hull[hull.size() - 2], hull.back(), cur)) {
            hull.pop_back();
        }
        hull.push_back(cur);
    }

    ll query(ll x) {
        while (hull.size() >= 2 && hull[1].eval(x) >= hull[0].eval(x)) {
            hull.pop_front();
        }
        return hull[0].eval(x);
    }
};

// ============================================================
// 3. MinConvexHullBS (Slope Menurun, Query x Acak / Non-Monoton)
// ============================================================
// Kompleksitas: Insert O(1) amortized, Query O(log N) via Binary Search
struct MinConvexHullBS {
    vector<Line> hull;

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

    ll query(ll x) const {
        int l = 0, r = (int)hull.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (hull[mid].eval(x) >= hull[mid + 1].eval(x)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return hull[l].eval(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TEMPLATE CONVEX HULL TRICK (KASUS MONOTON) ===\n";
    cout << "Modul 1: MinConvexHull (Deque O(1) amortized)\n";
    cout << "Modul 2: MaxConvexHull (Deque O(1) amortized)\n";
    cout << "Modul 3: MinConvexHullBS (Binary Search O(log N))\n";

    return 0;
}
