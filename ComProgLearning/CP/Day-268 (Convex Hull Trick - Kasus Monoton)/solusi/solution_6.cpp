/*
============================================================
✅ Solution 6: Memaksimalkan Keuntungan Investasi (Upper Convex Hull CHT)
============================================================
Approach: Upper Convex Hull Trick with Deque for Maximization
Complexity: Time O(N + Q) | Space O(N)
Key Insight:
1. Upper Convex Hull (Maksimum):
   - Garis diberikan dengan slope m tidak menurun (m_0 <= m_1 <= ...).
   - Kueri x diberikan tidak menurun (x_0 <= x_1 <= ...).

2. Uji Eliminasi Belakang untuk Upper Hull:
   Garis B di antara A dan C (A.m <= B.m <= C.m) tidak pernah menjadi yang paling atas jika
   titik potong A & B berada di sebelah kanan (atau sama dengan) titik potong B & C:
   x_{AB} >= x_{BC}
   (A.b - B.b) / (B.m - A.m) >= (B.b - C.b) / (C.m - B.m)
   <=> (A.b - B.b) * (C.m - B.m) >= (B.b - C.b) * (B.m - A.m).
   Gunakan __int128 untuk cross-product check.

3. Kueri Maju di Depan:
   Pada saat x bertambah, jika garis indeks 1 memberikan nilai >= garis indeks 0,
   maka garis indeks 0 boleh dibuang secara permanen dengan `pop_front()`.
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

struct UpperConvexHull {
    deque<Line> hull;

    // Untuk upper hull dengan slope menaik:
    // Garis b tidak berguna jika x_{ab} >= x_{bc}
    static bool is_bad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(a.b - b.b) * (c.m - b.m) >= (__int128)(b.b - c.b) * (b.m - a.m);
    }

    void add_line(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b >= b) return; // Simpan hanya intersep terbesar untuk maksimasi
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    UpperConvexHull uch;
    for (int i = 0; i < n; i++) {
        ll m, b;
        cin >> m >> b;
        uch.add_line(m, b);
    }

    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        cout << uch.query(x) << "\n";
    }

    return 0;
}
