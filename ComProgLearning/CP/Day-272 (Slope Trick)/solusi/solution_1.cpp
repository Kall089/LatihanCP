/*
============================================================
✅ Solution 1: Mengubah Barisan Menjadi Terurut Tidak Menurun
============================================================
Approach: Slope Trick with Single Max-Heap (Prefix Minimum)
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Prefiks Minimum:
   Fungsi transisi dp[i](x) = |x - a[i]| + min_{y <= x} dp[i-1](y).
   Operasi min_{y <= x} menghilangkan semua lereng dengan slope > 0.
   Oleh karena itu, kita hanya perlu mencatat breakpoint di mana slope bertambah dari negatif ke 0.
   Hal ini dapat direpresentasikan dengan sebuah Max-Heap `L`.

2. Menambahkan |x - a[i]|:
   - Jika a[i] < L.top():
     Titik a[i] berada di lereng menurun fungsi sebelumnya.
     Nilai minimum global bertambah sebesar (L.top() - a[i]).
     Puncak lama L.top() sekarang memiliki slope 0 (karena bertambah +1),
     sedangkan a[i] menambahkan dua breakpoint baru (dari -1 ke 0 dan 0 ke +1).
     Maka L.pop(), lalu L.push(a[i]) dua kali.
   - Jika a[i] >= L.top():
     Titik a[i] berada di daerah datar. Nilai minimum global tidak berubah.
     Cukup masukkan a[i] ke L.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_non_decreasing(int n, const vector<ll>& a) {
    priority_queue<ll> L;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        if (!L.empty() && a[i] < L.top()) {
            ans += L.top() - a[i];
            L.pop();
            L.push(a[i]);
            L.push(a[i]);
        } else {
            L.push(a[i]);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_non_decreasing(n, a) << "\n";

    return 0;
}
