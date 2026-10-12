/*
 * Day 20 — Sliding Window
 * File  : solution_3.cpp
 * Topik : Smallest Subarray with Sum >= S — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Variable-Size Sliding Window (Shortest pattern)
 *
 * Idea:
 *   - Expand R (selalu): sum += A[R]
 *   - WHILE sum >= S (window valid):
 *       update ans = min(ans, R - L + 1)
 *       sum -= A[L]; L++   (coba shrink)
 *   - Loop berakhir saat R = n-1.
 *
 * Mengapa Shortest pattern?
 *   - Kita ingin window TERPENDEK yang valid.
 *   - Selama window masih valid (sum >= S), kita coba mengecilkannya.
 *   - Saat tidak valid lagi, lanjut expand R.
 *
 * Pre-condition: A[i] > 0 (jika ada nol/negatif, sliding window
 *               sum bisa naik-turun → invariant rusak).
 *
 * Verifikasi sample 1: A=[2,1,5,2,3,2], S=7
 *   R=0: sum=2, !valid
 *   R=1: sum=3, !valid
 *   R=2: sum=8, valid → ans=3, sum-=2 → sum=6, L=1, !valid
 *   R=3: sum=8, valid → ans=min(3,3)=3, sum-=1 → sum=7, L=2, valid
 *                       ans=min(3,2)=2, sum-=5 → sum=2, L=3, !valid
 *   R=4: sum=5, !valid
 *   R=5: sum=7, valid → ans=min(2,3)=2, sum-=2 → sum=5, L=4, !valid
 *   Output: 2 ✓
 *
 * Verifikasi sample 3: A=[1,2,3,4], S=100
 *   Total sum = 10 < 100. ans tetap INT_MAX → output 0 ✓
 *
 * Complexity: O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll S;
    cin >> n >> S;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    int L = 0;
    int ans = INT_MAX;
    ll sum = 0;

    for (int R = 0; R < n; R++) {
        sum += A[R];                       // expand kanan

        while (sum >= S) {                 // selama valid → coba shrink
            ans = min(ans, R - L + 1);
            sum -= A[L];
            L++;
        }
    }

    cout << (ans == INT_MAX ? 0 : ans) << "\n";
    return 0;
}
