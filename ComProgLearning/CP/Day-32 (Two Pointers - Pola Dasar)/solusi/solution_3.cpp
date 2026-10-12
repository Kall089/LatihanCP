/*
 * Day 19 — Two Pointers
 * File  : solution_3.cpp
 * Topik : Container With Most Water — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Greedy Opposite Direction Two Pointers
 *
 * Idea:
 *   - L = 0, R = n-1
 *   - Volume saat ini: min(h[L], h[R]) * (R - L)
 *   - Update jawaban maksimal
 *   - Gerakkan pointer yang lebih KECIL:
 *     → Jika h[L] < h[R]: gerak L++ (pointer kanan tidak bisa dibuat lebih baik)
 *     → Jika h[L] >= h[R]: gerak R--
 *
 * Greedy Proof:
 *   Misalkan h[L] < h[R]. Volume = h[L] * (R-L).
 *   Jika kita gerak R ke R-1:
 *     Volume baru = min(h[L], h[R-1]) * (R-1-L)
 *     ≤ h[L] * (R-1-L) < h[L] * (R-L) = volume saat ini
 *   Jadi gerak R tidak akan meningkatkan volume → gerak L yang benar.
 *
 * Complexity: O(n) time, O(1) space
 *
 * Verifikasi sample:
 *   Sample 1: h=[1,8,6,2,5,4]
 *     L=0,R=5: min(1,4)*5=5   h[L]<h[R] → L++
 *     L=1,R=5: min(8,4)*4=16  h[L]>h[R] → R--   ans=16
 *     L=1,R=4: min(8,5)*3=15  h[L]>h[R] → R--
 *     L=1,R=3: min(8,2)*2=4   h[L]>h[R] → R--
 *     L=1,R=2: min(8,6)*1=6   h[L]>h[R] → R--
 *     L>=R, stop. Output: 16 ✓
 *
 *   Sample 2: h=[1,1]
 *     L=0,R=1: min(1,1)*1=1 → ans=1 ✓
 *
 *   Sample 3: h=[4,3,2,4]
 *     L=0,R=3: min(4,4)*3=12  h[L]=h[R] → R--  ans=12
 *     L=0,R=2: min(4,2)*2=4   h[L]>h[R] → R--
 *     L=0,R=1: min(4,3)*1=3   h[L]>h[R] → R--
 *     L>=R, stop. Output: 12
 *   (Note: Sample Output di exercise_3.cpp perlu dikoreksi menjadi 12)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> h(n);
    for (auto& x : h) cin >> x;

    int L = 0, R = n - 1;
    ll ans = 0;

    while (L < R) {
        ll vol = min(h[L], h[R]) * (ll)(R - L);
        ans = max(ans, vol);

        // Gerakkan pointer yang lebih kecil
        if (h[L] < h[R]) {
            L++;
        } else {
            R--;
        }
    }

    cout << ans << "\n";
    return 0;
}
