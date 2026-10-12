/*
============================================================
✅ Solution 3: Mengubah Barisan Menjadi Terurut Tidak Menaik (Suffix Minimum)
============================================================
Approach: Slope Trick with Single Min-Heap (Suffix Minimum)
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Sufiks Minimum:
   Fungsi transisi dp[i](x) = |x - a[i]| + min_{y >= x} dp[i-1](y).
   Operasi min_{y >= x} menghilangkan semua lereng dengan slope < 0 (lereng menurun).
   Oleh karena itu, kita hanya perlu mencatat breakpoint di mana slope bertambah dari 0 ke positif.
   Hal ini direpresentasikan dengan sebuah Min-Heap `R`.

2. Menambahkan |x - a[i]|:
   - Jika a[i] > R.top():
     Titik a[i] berada di lereng menaik fungsi sebelumnya.
     Nilai minimum global bertambah sebesar (a[i] - R.top()).
     Puncak lama R.top() sekarang memiliki slope 0,
     sedangkan a[i] menambahkan dua breakpoint baru (dari 0 ke +1 dan +1 ke +2).
     Maka R.pop(), lalu R.push(a[i]) dua kali.
   - Jika a[i] <= R.top():
     Titik a[i] berada di daerah datar. Cukup masukkan a[i] ke R.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_non_increasing(int n, const vector<ll>& a) {
    priority_queue<ll, vector<ll>, greater<ll>> R;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        if (!R.empty() && a[i] > R.top()) {
            ans += a[i] - R.top();
            R.pop();
            R.push(a[i]);
            R.push(a[i]);
        } else {
            R.push(a[i]);
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

    cout << solve_non_increasing(n, a) << "\n";

    return 0;
}
