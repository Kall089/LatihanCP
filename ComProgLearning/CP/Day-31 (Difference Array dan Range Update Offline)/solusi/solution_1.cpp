/*
============================================================
✅ Solution 1: Range Update Sederhana
============================================================
Approach: Difference Array 1D
Complexity: Time O(N + Q) | Space O(N)
Key Insight:
Update rentang tidak perlu menyentuh seluruh rentang. Cukup catat
di mana efeknya MULAI (l) dan di mana efeknya BERHENTI (r+1).
Prefix sum di akhir "menyalakan" efek itu sepanjang rentang yang benar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // n + 2 supaya indeks r+1 aman ketika r == n
    vector<ll> diff(n + 2, 0);

    for (int i = 0; i < q; i++) {
        int l, r;
        ll v;
        cin >> l >> r >> v;
        diff[l]     += v;   // mulai bertambah
        diff[r + 1] -= v;   // berhenti setelah r
    }

    // Rekonstruksi in-place: diff[i] menjadi nilai akhir a[i]
    for (int i = 1; i <= n; i++) diff[i] += diff[i - 1];

    for (int i = 1; i <= n; i++)
        cout << diff[i] << " \n"[i == n];

    return 0;
}
