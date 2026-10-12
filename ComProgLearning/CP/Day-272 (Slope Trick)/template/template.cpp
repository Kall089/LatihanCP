/*
============================================================
📦 TEMPLATE BOILERPLATE: Slope Trick Master Library
============================================================
Day: 272 | Topic: Slope Trick (Piecewise Linear Convex Function)
Standard: C++17 Competitive Programming Master Template

Struktur Data Slope Trick:
Memelihara fungsi konveks sepotong-sepotong kontinu f(x) dengan:
- `min_val`: Nilai minimum global fungsi pada daerah datar (slope = 0).
- `L`: Max-Heap untuk titik belok lereng kiri (slope < 0).
- `R`: Min-Heap untuk titik belok lereng kanan (slope > 0).
- `tag_L`, `tag_R`: Lazy tag pergeseran translasi (Minkowski sum).

Operasi yang didukung:
1. `add_abs(a)`: Menambahkan fungsi |x - a|.
2. `add_right(a)`: Menambahkan fungsi max(0, x - a).
3. `add_left(a)`: Menambahkan fungsi max(0, a - x).
4. `prefix_min()`: f(x) = min_{y <= x} f(y) (kosongkan R).
5. `suffix_min()`: f(x) = min_{y >= x} f(y) (kosongkan L).
6. `shift(dl, dr)`: f(x) = min_{y in [x - dr, x - dl]} f(y) (tag_L += dl, tag_R += dr).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class SlopeTrick {
public:
    ll min_val;
    ll tag_L, tag_R;
    priority_queue<ll> L;                                // Max-heap untuk lereng kiri
    priority_queue<ll, vector<ll>, greater<ll>> R;       // Min-heap untuk lereng kanan

    SlopeTrick() : min_val(0), tag_L(0), tag_R(0) {}

    // Mengembalikan batas kiri dan kanan dari daerah datar (slope = 0)
    pair<ll, ll> get_optimum_range() const {
        ll l = L.empty() ? -1e18 : L.top() + tag_L;
        ll r = R.empty() ? 1e18 : R.top() + tag_R;
        return {l, r};
    }

    // Menambahkan fungsi |x - a|
    void add_abs(ll a) {
        add_left(a);
        add_right(a);
    }

    // Menambahkan fungsi max(0, x - a) -> menambah slope lereng kanan
    void add_right(ll a) {
        ll l_top = L.empty() ? -1e18 : L.top() + tag_L;
        if (a < l_top) {
            min_val += l_top - a;
            L.pop();
            L.push(a - tag_L);
            R.push(l_top - tag_R);
        } else {
            R.push(a - tag_R);
        }
    }

    // Menambahkan fungsi max(0, a - x) -> menambah slope lereng kiri
    void add_left(ll a) {
        ll r_top = R.empty() ? 1e18 : R.top() + tag_R;
        if (a > r_top) {
            min_val += a - r_top;
            R.pop();
            R.push(a - tag_R);
            L.push(r_top - tag_L);
        } else {
            L.push(a - tag_L);
        }
    }

    // f(x) = min_{y <= x} f(y) -> potong semua slope positif
    void prefix_min() {
        while (!R.empty()) R.pop();
    }

    // f(x) = min_{y >= x} f(y) -> potong semua slope negatif
    void suffix_min() {
        while (!L.empty()) L.pop();
    }

    // Minkowski sum dengan [dl, dr]: f(x) = min_{y in [x - dr, x - dl]} f(y)
    void shift(ll dl, ll dr) {
        tag_L += dl;
        tag_R += dr;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== MASTER BOILERPLATE SLOPE TRICK ===\n";
    cout << "Objek SlopeTrick mendukung: add_abs, add_right, add_left, prefix_min, suffix_min, shift\n";

    return 0;
}
