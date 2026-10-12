/*
============================================================
✅ Solution 1: Tarif Angkot di Hari Festival (Static Lines Monotone CHT)
============================================================
Approach: Convex Hull Trick with Deque
Complexity: Time O(N + Q) | Space O(N)
Key Insight:
1. Kondisi Monoton:
   - Garis diberikan dengan slope m tidak menaik (m_0 >= m_1 >= ...).
   - Kueri x diberikan tidak menurun (x_0 <= x_1 <= ...).
   Hal ini memungkinkan penggunaan Deque dengan amortized O(1) per operasi.

2. Uji Eliminasi Belakang:
   Garis tengah B di antara A dan C dibuang jika titik potong (A, B) >= titik potong (B, C):
   (B.b - A.b) / (A.m - B.m) >= (C.b - B.b) / (B.m - C.m)
   <=> (B.b - A.b) * (B.m - C.m) >= (C.b - B.b) * (A.m - B.m).
   Perkalian silang dilakukan dengan `__int128` untuk mencegah integer overflow.

3. Kueri Maju di Depan:
   Karena x bertambah, jika garis ke-1 lebih baik daripada garis ke-0, garis ke-0
   tidak akan pernah optimal lagi, sehingga dibuang dengan `pop_front()`.
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

    // Mengembalikan true jika garis b membuat garis usang di hadapan a dan c
    static bool is_bad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(b.b - a.b) * (b.m - c.m) >= (__int128)(c.b - b.b) * (a.m - b.m);
    }

    void add_line(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b) return; // Garis yang sudah ada lebih baik di semua x
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

    int n, q;
    if (!(cin >> n >> q)) return 0;

    ConvexHull ch;
    for (int i = 0; i < n; i++) {
        ll m, b;
        cin >> m >> b;
        ch.add_line(m, b);
    }

    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        cout << ch.query(x) << "\n";
    }

    return 0;
}
