/*
============================================================
✅ Solution 3: Promo Hanya untuk Zona Tertentu (Line Segments Li Chao)
============================================================
Approach: Segment Tree + Li Chao Tree for Range Segments [L, R]
Complexity: Time O(Q log^2 Q) | Space O(Q)
Key Insight:
1. Dekomposisi Rentang:
   Sebuah garis yang hanya aktif pada rentang [L, R] tidak boleh mempengaruhi titik di luar rentang.
   Kita pecah interval [L, R] menjadi O(log Q) simpul kanonik pada segment tree di atas koordinat kueri x.

2. Insersi Li Chao Lokal:
   Pada setiap simpul kanonik yang tercakup utuh di dalam [L, R], kita masukkan garis tersebut
   menggunakan prosedur `add_line_internal` Li Chao Tree standar.
   Karena ada O(log Q) simpul kanonik dan setiap operasi memakan O(log Q), total waktu adalah O(log^2 Q).

3. Evaluasi Kueri:
   Kueri pada titik x tetap menelusuri jalur dari akar ke daun, mengevaluasi seluruh segmen garis
   yang tersimpan di simpul-simpul pada jalur tersebut dalam waktu O(log Q).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct Line {
    ll m = 0, b = INF;
    ll eval(ll x) const {
        if (b >= INF / 2) return INF;
        return m * x + b;
    }
};

struct LiChaoSegmentTree {
    int n;
    vector<ll> coords;
    vector<Line> tree;

    LiChaoSegmentTree(const vector<ll>& pts) {
        coords = pts;
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        n = coords.size();
        tree.assign(4 * max(n, 1) + 4, Line{});
    }

    void add_line_internal(Line new_line, int v, int l, int r) {
        int mid = l + (r - l) / 2;
        bool left_better = new_line.eval(coords[l]) < tree[v].eval(coords[l]);
        bool mid_better  = new_line.eval(coords[mid]) < tree[v].eval(coords[mid]);

        if (mid_better) {
            swap(new_line, tree[v]);
        }
        if (l == r) return;

        if (left_better != mid_better) {
            add_line_internal(new_line, 2 * v, l, mid);
        } else {
            add_line_internal(new_line, 2 * v + 1, mid + 1, r);
        }
    }

    void add_segment(Line line, ll ql, ll qr, int v, int l, int r) {
        if (coords[r] < ql || coords[l] > qr) return;
        if (ql <= coords[l] && coords[r] <= qr) {
            add_line_internal(line, v, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        add_segment(line, ql, qr, 2 * v, l, mid);
        add_segment(line, ql, qr, 2 * v + 1, mid + 1, r);
    }

    void add_segment(ll m, ll b, ll l, ll r) {
        if (n == 0) return;
        add_segment(Line{m, b}, l, r, 1, 0, n - 1);
    }

    ll query_internal(ll x_val, int v, int l, int r) {
        ll ans = tree[v].eval(x_val);
        if (l == r) return ans;

        int mid = l + (r - l) / 2;
        if (x_val <= coords[mid]) {
            return min(ans, query_internal(x_val, 2 * v, l, mid));
        } else {
            return min(ans, query_internal(x_val, 2 * v + 1, mid + 1, r));
        }
    }

    ll query(ll x_val) {
        if (n == 0) return INF;
        return query_internal(x_val, 1, 0, n - 1);
    }
};

struct Op {
    int type;
    ll m, b, l, r, x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    vector<Op> ops(q);
    vector<ll> query_pts;

    for (int i = 0; i < q; i++) {
        cin >> ops[i].type;
        if (ops[i].type == 1) {
            cin >> ops[i].m >> ops[i].b >> ops[i].l >> ops[i].r;
        } else {
            cin >> ops[i].x;
            query_pts.push_back(ops[i].x);
        }
    }

    LiChaoSegmentTree lct(query_pts);

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 1) {
            lct.add_segment(ops[i].m, ops[i].b, ops[i].l, ops[i].r);
        } else {
            ll ans = lct.query(ops[i].x);
            if (ans >= INF / 2) {
                cout << "EMPTY\n";
            } else {
                cout << ans << "\n";
            }
        }
    }

    return 0;
}
