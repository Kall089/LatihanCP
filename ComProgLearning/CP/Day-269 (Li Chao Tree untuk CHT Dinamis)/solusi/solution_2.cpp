/*
============================================================
✅ Solution 2: Katak di Pegunungan Acak (Non-Monotone Frog Jump)
============================================================
Approach: Li Chao Tree for Dynamic CHT with Arbitrary Coordinates
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Rekurensi Kuadratik:
   dp[i] = h[i]^2 + C + min_{j < i} ( (-2 * h[j]) * h[i] + (dp[j] + h[j]^2) ).

2. Ketinggian Non-Monoton:
   Karena h[i] tidak terurut naik/turun, kemiringan garis (-2 * h[j]) dan kueri (h[i])
   keduanya datang dalam urutan acak. Deque standar tidak berlaku.
   Li Chao Tree menangani garis dan kueri acak ini dalam O(log N).

3. Urutan Kronologis:
   Garis dari batu j hanya boleh dimasukkan ke dalam Li Chao Tree SETELAH dp[j] terhitung.
   Untuk batu 0: dp[0] = 0, garis pertama = Line(-2 * h[0], h[0]^2).
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
    ll c;
    if (!(cin >> n >> c)) return 0;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    LiChaoTree lct(h);
    vector<ll> dp(n, 0);

    dp[0] = 0;
    lct.add_line(-2 * h[0], dp[0] + h[0] * h[0]);

    for (int i = 1; i < n; i++) {
        ll best = lct.query(h[i]);
        dp[i] = h[i] * h[i] + c + best;
        lct.add_line(-2 * h[i], dp[i] + h[i] * h[i]);
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
