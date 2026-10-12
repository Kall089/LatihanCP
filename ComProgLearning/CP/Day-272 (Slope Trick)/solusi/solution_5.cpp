/*
============================================================
✅ Solution 5: Penataan Barisan dengan Batas Selisih Umum [D_min, D_max]
============================================================
Approach: General Slope Trick (2 Priority Queues with Independent Interval Offsets)
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Konvolusi Minkowski Interval Umum:
   Syarat D_min <= b[i] - b[i-1] <= D_max setara dengan:
   b[i-1] in [b[i] - D_max, b[i] - D_min].
   Operasi min terhadap rentang ini memperluas lembah minimum fungsi f_{i-1}(x):
   - Titik awal daerah minimum bergeser ke kanan sebesar D_min: tag_L += D_min.
   - Titik akhir daerah minimum bergeser ke kanan sebesar D_max: tag_R += D_max.

2. Penambahan Nilai Mutlak |x - a[i]|:
   Evaluasi nilai a[i] terhadap l_top = L.top() + tag_L dan r_top = R.top() + tag_R:
   - Jika a[i] < l_top: min_val += l_top - a[i], seimbangkan dengan transfer L.top() ke R.
   - Jika a[i] > r_top: min_val += a[i] - r_top, seimbangkan dengan transfer R.top() ke L.
   - Jika di tengah: cukup sisipkan ke kedua heap.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_general_bounds(int n, ll d_min, ll d_max, const vector<ll>& a) {
    priority_queue<ll> L;
    priority_queue<ll, vector<ll>, greater<ll>> R;

    ll tag_L = 0, tag_R = 0;
    ll min_val = 0;

    L.push(a[0]);
    R.push(a[0]);

    for (int i = 1; i < n; i++) {
        tag_L += d_min;
        tag_R += d_max;

        ll cur_a = a[i];
        ll l_top = L.top() + tag_L;
        ll r_top = R.top() + tag_R;

        if (cur_a < l_top) {
            min_val += l_top - cur_a;
            L.pop();
            L.push(cur_a - tag_L);
            L.push(cur_a - tag_L);
            R.push(l_top - tag_R);
        } else if (cur_a > r_top) {
            min_val += cur_a - r_top;
            R.pop();
            R.push(cur_a - tag_R);
            R.push(cur_a - tag_R);
            L.push(r_top - tag_L);
        } else {
            L.push(cur_a - tag_L);
            R.push(cur_a - tag_R);
        }
    }

    return min_val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll d_min, d_max;
    if (!(cin >> n >> d_min >> d_max)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_general_bounds(n, d_min, d_max, a) << "\n";

    return 0;
}
