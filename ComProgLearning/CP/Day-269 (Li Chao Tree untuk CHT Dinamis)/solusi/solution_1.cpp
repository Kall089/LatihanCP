/*
============================================================
✅ Solution 1: Papan Tarif yang Terus Berubah (Dynamic Li Chao Tree)
============================================================
Approach: Offline Coordinate Compression + Li Chao Tree
Complexity: Time O(Q log Q) | Space O(Q)
Key Insight:
1. Penanganan Koordinat Kueri:
   Kueri x bisa berada di sembarang bilangan bulat dalam [-10^6, 10^6].
   Kita kumpulkan seluruh nilai kueri x, lakukan sort & unique, lalu bangun Li Chao Tree
   di atas array koordinat terkompresi.

2. Invariant Li Chao Tree:
   Setiap simpul mewakili rentang indeks [l, r] dengan mid = (l + r) / 2.
   Simpul menyimpan garis yang memberikan nilai minimum pada titik x[mid].
   Garis yang kalah diturunkan ke anak kiri atau kanan tempat garis tersebut masih memiliki potensi menang.

3. Kueri Jalur:
   Kueri pada koordinat kueri x menelusuri jalur dari akar hingga daun yang memuat x,
   dan mengambil nilai minimum dari semua garis yang tersimpan di simpul-simpul jalur tersebut.
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

struct LiChaoTree {
    int n;
    vector<ll> coords;
    vector<Line> tree;

    LiChaoTree(const vector<ll>& pts) {
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

    void add_line(ll m, ll b) {
        if (n == 0) return;
        add_line_internal(Line{m, b}, 1, 0, n - 1);
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

struct QueryOp {
    int type;
    ll m, b, x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    vector<QueryOp> ops(q);
    vector<ll> query_coords;

    for (int i = 0; i < q; i++) {
        cin >> ops[i].type;
        if (ops[i].type == 1) {
            cin >> ops[i].m >> ops[i].b;
        } else {
            cin >> ops[i].x;
            query_coords.push_back(ops[i].x);
        }
    }

    LiChaoTree lct(query_coords);

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 1) {
            lct.add_line(ops[i].m, ops[i].b);
        } else {
            ll res = lct.query(ops[i].x);
            if (res >= INF / 2) {
                cout << "EMPTY\n";
            } else {
                cout << res << "\n";
            }
        }
    }

    return 0;
}
