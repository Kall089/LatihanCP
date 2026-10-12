/*
============================================================
✅ Solution 4: Mengatur Posisi Titik dengan Batas Jarak Maksimum (Lazy Tags)
============================================================
Approach: Slope Trick with Two Priority Queues (Max-Heap L & Min-Heap R) + Lazy Tags
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Infimal Convolution / Minkowski Sum:
   Transisi dp[i](x) = |x - a[i]| + min_{x - D <= y <= x + D} dp[i-1](y).
   Operasi pelebaran minimum sejauh [-D, D] menggeser seluruh lereng kiri ke kiri sebesar D,
   dan seluruh lereng kanan ke kanan sebesar D.
   Hal ini dapat dimodelkan secara efisien dengan dua variabel lazy tag:
   - tag_L -= D
   - tag_R += D

2. Penambahan Fungsi |x - a[i]|:
   Bandingkan nilai a[i] dengan puncak aktual:
   l_top = L.top() + tag_L
   r_top = R.top() + tag_R
   - Jika a[i] < l_top:
     min_val += l_top - a[i]
     Puncak lama L berpindah ke R (disesuaikan dengan tag_R),
     lalu a[i] dimasukkan dua kali ke L (disesuaikan dengan tag_L).
   - Jika a[i] > r_top:
     min_val += a[i] - r_top
     Puncak lama R berpindah ke L (disesuaikan dengan tag_L),
     lalu a[i] dimasukkan dua kali ke R (disesuaikan dengan tag_R).
   - Jika l_top <= a[i] <= r_top:
     a[i] dimasukkan ke L dan R tanpa mengubah min_val.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_bounded_distance(int n, ll d, const vector<ll>& a) {
    priority_queue<ll> L;
    priority_queue<ll, vector<ll>, greater<ll>> R;

    ll tag_L = 0, tag_R = 0;
    ll min_val = 0;

    // Base case: elemen pertama i = 0
    L.push(a[0]);
    R.push(a[0]);

    for (int i = 1; i < n; i++) {
        tag_L -= d;
        tag_R += d;

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
    ll d;
    if (!(cin >> n >> d)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_bounded_distance(n, d, a) << "\n";

    return 0;
}
