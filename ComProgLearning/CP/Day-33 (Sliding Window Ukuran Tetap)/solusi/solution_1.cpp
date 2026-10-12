/*
 * Day 20 — Sliding Window
 * File  : solution_1.cpp
 * Topik : Maximum Sum Subarray Size K — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Fixed-Size Sliding Window
 *
 * Idea:
 *   - Hitung sum window pertama [0..K-1]
 *   - Slide: sum += A[i] - A[i-K]  (masuk baru, keluar lama)
 *   - Setiap slide O(1) → total O(n)
 *
 * Verifikasi sample:
 *   Sample 1: A=[2,1,5,1,3,2], K=3
 *     window [2,1,5] → sum=8, ans=8
 *     i=3: sum=8+A[3]-A[0]=8+1-2=7, ans=8
 *     i=4: sum=7+A[4]-A[1]=7+3-1=9, ans=9
 *     i=5: sum=9+A[5]-A[2]=9+2-5=6, ans=9 ✓
 *
 *   Sample 2: A=[4,7,1,8,3], K=2
 *     window [4,7] → sum=11
 *     i=2: 11+1-4=8, ans=11
 *     i=3: 8+8-7=9, ans=11
 *     i=4: 9+3-1=11, ans=11 ✓
 *
 *   Sample 3: A=[1,2,3,4], K=4
 *     window [1,2,3,4] → sum=10, no slide → ans=10 ✓
 *
 * Complexity: O(n) time, O(1) extra space
 *
 * Edge cases:
 *   - n == k: tidak ada slide, output = sum window pertama
 *   - n == 1, k == 1: output = A[0]
 *   - elemen negatif: tetap valid (max bisa negatif juga)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    // Step 1: Hitung sum window pertama [0..k-1]
    ll sum = 0;
    for (int i = 0; i < k; i++) sum += A[i];
    ll ans = sum;

    // Step 2: Slide window dari index k sampai n-1
    for (int i = k; i < n; i++) {
        sum += A[i] - A[i - k];   // tambah baru, kurangi lama
        ans = max(ans, sum);
    }

    cout << ans << "\n";
    return 0;
}
