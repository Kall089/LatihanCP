/*
============================================================
✅ Solution 5: Partisi Pasangan Kembar Minimum (Two-Pointer D&C DP)
============================================================
Approach: Divide and Conquer DP Optimization with Stateful Sliding Pointers
Complexity: Time O(K * N log N) | Space O(N)
Key Insight:
1. Sifat Monge Jumlah Pasangan Sama:
   Jika kita memperluas interval, penambahan jumlah pasangan sama memenuhi:
   C(a, c) + C(b, d) <= C(a, d) + C(b, c) untuk a <= b <= c <= d.
   Dengan demikian, titik transisi optimal opt[g][i] monoton tidak menurun.

2. Pemeliharaan Biaya dengan Dua Pointer (Mo-Style):
   Karena menghitung C(l, r) dari nol memakan waktu O(N), kita pertahankan interval aktif
   [cur_l, cur_r] beserta array frekuensi `cnt` dan total `current_cost`.
   Saat memperluas/memperpendek jendela:
   - Tambah elemen x: current_cost += cnt[x]++;
   - Hapus elemen x: current_cost -= --cnt[x];

3. Amortisasi Pergeseran Pointer:
   Pada satu level rekursi D&C:
   - Rentang [opt_l, opt_r] di seluruh node pada kedalaman yang sama saling lepas atau bertumpukan terbatas,
     sehingga total pergerakan cur_l <= O(N).
   - Nilai mid bergerak secara teratur, pergerakan cur_r <= O(N).
   Dengan kedalaman O(log N), total pergerakan pointer per layer adalah O(N log N).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // Stateful Two-Pointer Sliding Window
    int cur_l = 1, cur_r = 0;
    ll cur_cost = 0;
    vector<int> cnt(n + 1, 0);

    auto add = [&](int idx) {
        cur_cost += cnt[a[idx]];
        cnt[a[idx]]++;
    };

    auto remove = [&](int idx) {
        cnt[a[idx]]--;
        cur_cost -= cnt[a[idx]];
    };

    auto get_cost = [&](int l, int r) -> ll {
        while (cur_r < r) add(++cur_r);
        while (cur_l > l) add(--cur_l);
        while (cur_r > r) remove(cur_r--);
        while (cur_l < l) remove(cur_l++);
        return cur_cost;
    };

    vector<ll> dp_prev(n + 1, INF);
    vector<ll> dp_curr(n + 1, INF);
    dp_prev[0] = 0;

    for (int g = 1; g <= k; g++) {
        fill(dp_curr.begin(), dp_curr.end(), INF);

        function<void(int, int, int, int)> compute = [&](int l, int r, int opt_l, int opt_r) {
            if (l > r) return;

            int mid = l + (r - l) / 2;
            int best_j = opt_l;
            ll best_val = INF;

            for (int j = opt_l; j <= min(opt_r, mid - 1); j++) {
                if (dp_prev[j] == INF) continue;
                ll cand = dp_prev[j] + get_cost(j + 1, mid);
                if (cand < best_val) {
                    best_val = cand;
                    best_j = j;
                }
            }

            dp_curr[mid] = best_val;

            compute(l, mid - 1, opt_l, best_j);
            compute(mid + 1, r, best_j, opt_r);
        };

        compute(g, n, g - 1, n - 1);
        dp_prev = dp_curr;
    }

    cout << dp_prev[n] << "\n";

    return 0;
}
