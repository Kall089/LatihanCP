/*
============================================================
✅ Solution 4: Relai Komunikasi Acak (Arbitrary Kalila & Dimna)
============================================================
Approach: Li Chao Tree with Coordinate Compression
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Rekurensi:
   dp[i] = min_{j < i} (dp[j] + b[j] * a[i]).
   Basis: dp[0] = 0.

2. Ketidakmonotonan:
   Karena a[i] dan b[i] tidak terurut, CHT Deque akan gagal total.
   Li Chao Tree menangani baik penambahan garis acak maupun evaluasi kueri acak dalam O(log N).

3. Koordinat Kueri:
   Semua kueri dilakukan pada nilai titik a[i], sehingga domain koordinat Li Chao Tree
   dapat dibatasi secara presisi pada himpunan unik seluruh elemen array a.
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    LiChaoTree lct(a);
    vector<ll> dp(n, 0);

    dp[0] = 0;
    lct.add_line(b[0], dp[0]);

    for (int i = 1; i < n; i++) {
        dp[i] = lct.query(a[i]);
        lct.add_line(b[i], dp[i]);
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
