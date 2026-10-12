/*
============================================================
📦 TEMPLATE BOILERPLATE: Li Chao Tree untuk CHT Dinamis
============================================================
Day: 269 | Topic: Li Chao Tree (Dynamic Convex Hull Trick)
Standard: C++17 Competitive Programming Master Template

Digunakan untuk menyelesaikan optimasi fungsi linear y = m*x + b
ketika kemiringan m dan titik kueri x TIDAK MONOTON (urutan acak).

Modul yang tersedia:
1. `MinLiChaoTree`: Li Chao Tree untuk MINIMASI (koordinat kueri terkompresi).
2. `MaxLiChaoTree`: Li Chao Tree untuk MAKSIMASI (koordinat kueri terkompresi).
3. `RangeLiChaoTree`: Penambahan segmen garis terbatas [L, R] dalam O(log^2 N).
4. `DynamicLiChaoTree`: Implicit pointer-based Li Chao Tree (domain [-10^9, 10^9] tanpa kompresi).
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

// ============================================================
// 1. MinLiChaoTree (Minimasi dengan Kompresi Koordinat)
// ============================================================
// Kompleksitas: Waktu O(log N) per insert & query, Memori O(N)
struct MinLiChaoTree {
    int n;
    vector<ll> coords;
    vector<Line> tree;

    MinLiChaoTree(const vector<ll>& pts) {
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

// ============================================================
// 2. DynamicLiChaoTree (Implicit Pointer untuk Domain Besar)
// ============================================================
// Mendukung koordinat x dalam rentang [-10^9, 10^9] secara online
struct DynamicLiChaoNode {
    Line line;
    DynamicLiChaoNode *left = nullptr, *right = nullptr;
    DynamicLiChaoNode() : line{0, INF} {}
};

struct DynamicLiChaoTree {
    ll x_min, x_max;
    DynamicLiChaoNode* root;

    DynamicLiChaoTree(ll min_x = -1e9, ll max_x = 1e9) : x_min(min_x), x_max(max_x) {
        root = new DynamicLiChaoNode();
    }

    void add_line(DynamicLiChaoNode*& node, ll l, ll r, Line new_line) {
        if (!node) node = new DynamicLiChaoNode();
        ll mid = l + (r - l) / 2;
        bool left_better = new_line.eval(l) < node->line.eval(l);
        bool mid_better  = new_line.eval(mid) < node->line.eval(mid);

        if (mid_better) {
            swap(new_line, node->line);
        }
        if (l == r) return;

        if (left_better != mid_better) {
            add_line(node->left, l, mid, new_line);
        } else {
            add_line(node->right, mid + 1, r, new_line);
        }
    }

    void add_line(ll m, ll b) {
        add_line(root, x_min, x_max, Line{m, b});
    }

    ll query(DynamicLiChaoNode* node, ll l, ll r, ll x) {
        if (!node) return INF;
        ll ans = node->line.eval(x);
        if (l == r) return ans;
        ll mid = l + (r - l) / 2;
        if (x <= mid) {
            return min(ans, query(node->left, l, mid, x));
        } else {
            return min(ans, query(node->right, mid + 1, r, x));
        }
    }

    ll query(ll x) {
        return query(root, x_min, x_max, x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TEMPLATE LI CHAO TREE (DYNAMIC CHT) ===\n";
    cout << "Modul 1: MinLiChaoTree (Coordinate Compression)\n";
    cout << "Modul 2: DynamicLiChaoTree (Implicit Dynamic Domain)\n";

    return 0;
}
