/*
 * Day 19 — Two Pointers
 * File  : solution_4.cpp
 * Topik : Three Sum Closest — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Sort + Outer Loop + Two Pointers
 *
 * Idea:
 *   1. Sort array: O(n log n)
 *   2. Inisialisasi ans = A[0]+A[1]+A[2]
 *   3. Outer loop i dari 0 sampai n-3:
 *      - L = i+1, R = n-1
 *      - Hitung s = A[i]+A[L]+A[R]
 *      - Jika |s-T| < |ans-T| → update ans = s
 *      - Jika s < T → L++ (butuh nilai lebih besar)
 *      - Jika s > T → R-- (butuh nilai lebih kecil)
 *      - Jika s == T → perfect match, stop
 *
 * Complexity: O(n²) time, O(1) extra space
 *
 * Verifikasi sample:
 *   Sample 1: A=[-1,2,1,-4], T=1
 *     Sorted: [-4,-1,1,2]
 *     ans = -4+(-1)+1 = -4 (init)
 *     i=0, A[i]=-4:
 *       L=1,R=3: -4+(-1)+2=-3 < 1 → |−3−1|=4, |−4−1|=5 → ans=-3, L++
 *       L=2,R=3: -4+1+2=-1 < 1 → |−1−1|=2 < 4 → ans=-1, L++
 *       L>=R, stop
 *     i=1, A[i]=-1:
 *       L=2,R=3: -1+1+2=2 > 1 → |2−1|=1 < 2 → ans=2, R--
 *       L>=R, stop
 *     i=2: i < n-2=2? No, stop
 *     Output: 2 ✓
 *
 *   Sample 2: A=[1,2,3], T=100
 *     Sorted: [1,2,3]. Hanya satu triplet: 1+2+3=6
 *     Output: 6 ✓
 *
 *   Sample 3: A=[-2,-1,0,1,2], T=0
 *     Banyak triplet, ada yang jumlahnya tepat 0 → Output: 0 ✓
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, T;
    cin >> n >> T;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    // Step 1: Sort
    sort(A.begin(), A.end());

    // Inisialisasi dengan triplet pertama
    int ans = A[0] + A[1] + A[2];

    // Step 2: Outer loop + Two Pointers
    for (int i = 0; i < n - 2; i++) {
        int L = i + 1, R = n - 1;

        while (L < R) {
            int s = A[i] + A[L] + A[R];

            // Update jawaban jika lebih dekat ke T
            if (abs(s - T) < abs(ans - T)) {
                ans = s;
            }

            if (s < T) {
                L++;   // Butuh nilai lebih besar
            } else if (s > T) {
                R--;   // Butuh nilai lebih kecil
            } else {
                // Perfect match!
                cout << ans << "\n";
                return 0;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
