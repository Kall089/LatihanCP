/*
 * Day 19 — Two Pointers
 * File  : solution_1.cpp
 * Topik : Two Sum Sorted Array — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Opposite Direction Two Pointers
 *
 * Idea:
 *   - L = 0 (kiri), R = N-1 (kanan)
 *   - sum < T → L++ (butuh nilai lebih besar, geser kiri)
 *   - sum > T → R-- (butuh nilai lebih kecil, geser kanan)
 *   - sum == T → FOUND!
 *   - L >= R → IMPOSSIBLE
 *
 * Correctness proof:
 *   Jika A[L]+A[R] > T, maka A[R] tidak bisa berpasangan dengan
 *   elemen apapun di kanan L (karena A[i] >= A[L] untuk i>L,
 *   sehingga A[i]+A[R] >= A[L]+A[R] > T). R bisa diturunkan.
 *
 * Complexity: O(n) time, O(1) space
 *
 * Verifikasi sample:
 *   Sample 1: A=[1,3,4,6,8,9], T=10
 *     L=0,R=5: 1+9=10 → FOUND → output "1 6" ✓
 *   Sample 2: A=[1,3,4,6,8,9], T=7
 *     L=0,R=5: 1+9=10>7 → R--
 *     L=0,R=4: 1+8=9>7  → R--
 *     L=0,R=3: 1+6=7=7  → FOUND → output "1 4" ✓
 *   Sample 3: A=[1,2,3,4], T=10
 *     semua kombinasi < 10 → IMPOSSIBLE ✓
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;
    ll T;
    cin >> T;

    int L = 0, R = n - 1;
    bool found = false;

    while (L < R) {
        ll s = A[L] + A[R];
        if (s == T) {
            cout << L + 1 << " " << R + 1 << "\n";
            found = true;
            break;
        } else if (s < T) {
            L++;   // sum terlalu kecil → naikkan L
        } else {
            R--;   // sum terlalu besar → turunkan R
        }
    }

    if (!found) {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
