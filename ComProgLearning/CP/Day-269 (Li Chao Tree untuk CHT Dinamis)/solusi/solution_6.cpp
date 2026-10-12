/*
============================================================
✅ Solution 6: Memaksimalkan Nilai Portofolio Dinamis (Max Li Chao Tree)
============================================================
Approach: Max Li Chao Tree for Dynamic CHT Maximization
Complexity: Time O(Q log Q) | Space O(Q)
Key Insight:
1. Upper Hull via Li Chao Tree:
   Untuk kasus maksimasi, simpul menyimpan garis yang memberikan nilai MAKSIMUM pada titik tengah mid.
   Basis inisialisasi garis pohon adalah Line(m = 0, b = -INF).

2. Transisi Penukaran (Swap):
   Jika new_line.eval(mid) > tree[v].eval(mid), lakukan swap(new_line, tree[v]).
   Kemudian garis yang kalah diturunkan ke sisi di mana ia memiliki peluang mengalahkan garis pemenang:
   yaitu sisi anak kiri jika new_line.eval(l) > tree[v].eval(l), atau ke anak kanan jika sebaliknya.

3. Kueri Jalur:
   Mengambil nilai maksimum di sepanjang lintasan akar hingga daun.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct Line {
    ll m = 0, b = -INF;
    ll eval(ll x) const {
        if (b <= -INF / 2) return -INF;
        return m * x + b;
    }
};

struct MaxLiChaoTree {
    int n;
    vector<ll> coords;
    vector<Line> tree;

    MaxLiChaoTree(const vector<ll>& pts) {
        coords = pts;
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        n = coords.size();
        tree.assign(4 * max(n, 1) + 4, Line{});
    }

    void add_line_internal(Line new_line, int v, int l, int r) {
        int mid = l + (r - l) / 2;
        bool left_better = new_line.eval(coords[l]) > tree[v].eval(coords[l]);
        bool mid_better  = new_line.eval(coords[mid]) > tree[v].eval(coords[mid]);

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

    void add_line(ll m, ll b) {
        if (n == 0) return;
        add_line_internal(Line{m, b}, 1, 0, n - 1);
    }

    ll query_internal(ll x_val, int v, int l, int r) {
        ll ans = tree[v].eval(x_val);
        if (l == r) return ans;

        int mid = l + (r - l) / 2;
        if (x_val <= coords[mid]) {
            return max(ans, query_internal(x_val, 2 * v, l, mid));
        } else {
            return max(ans, query_internal(x_val, 2 * v + 1, mid + 1, r));
        }
    }

    ll query(ll x_val) {
        if (n == 0) return -INF;
        return query_internal(x_val, 1, 0, n - 1);
    }
};

struct Op {
    int type;
    ll m, b, x;
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
            cin >> ops[i].m >> ops[i].b;
        } else {
            cin >> ops[i].x;
            query_pts.push_back(ops[i].x);
        }
    }

    MaxLiChaoTree mlct(query_pts);

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 1) {
            mlct.add_line(ops[i].m, ops[i].b);
        } else {
            ll ans = mlct.query(ops[i].x);
            if (ans <= -INF / 2) {
                cout << "EMPTY\n";
            } else {
                cout << ans << "\n";
            }
        }
    }

    return 0;
}
