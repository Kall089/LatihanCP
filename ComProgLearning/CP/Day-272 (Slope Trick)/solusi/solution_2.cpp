/*
============================================================
✅ Solution 2: Mengubah Barisan Menjadi Terurut Tegas Menaik (CF 713C)
============================================================
Approach: Index Transformation (a[i] - i) + Slope Trick with Max-Heap
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Reduksi Indeks Matematis:
   Untuk bilangan bulat b[i], syarat b[0] < b[1] < ... < b[N-1] ekivalen dengan:
   b[i] - b[i-1] >= 1
   <=> b[i] - i >= b[i-1] - (i - 1).
   Mendefinisikan b'[i] = b[i] - i menghasilkan syarat b'[i] >= b'[i-1] (non-decreasing).
   Dengan mendefinisikan a'[i] = a[i] - i, fungsi tujuan menjadi:
   sum |a[i] - b[i]| = sum |a'[i] - b'[i]|.

2. Slope Trick:
   Memelihara prefiks minimum DP dengan Max-Heap pada array a'.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_strictly_increasing(int n, vector<ll>& a) {
    for (int i = 0; i < n; i++) {
        a[i] -= i;
    }

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

    cout << solve_strictly_increasing(n, a) << "\n";

    return 0;
}
