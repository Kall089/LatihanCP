/*
 * Day 20 — Sliding Window
 * File  : exercise_3.cpp
 * Topik : Smallest Subarray with Sum >= S (Variable-Size Window)
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat POSITIF dan target S.
 * Cari panjang subarray kontinu TERPENDEK yang sum-nya >= S.
 * Jika tidak ada subarray yang memenuhi, output 0.
 *
 * Pendekatan VARIABLE-SIZE SLIDING WINDOW (Shortest):
 *   - Expand R: tambah A[R] ke sum
 *   - Shrink WHILE sum >= S: update ans, lalu sum -= A[L]; L++
 *
 * Input format  : Baris 1: N dan S (1 ≤ N ≤ 200.000, 1 ≤ S ≤ 10^14)
 *                 Baris 2: N bilangan bulat positif
 * Output format : panjang subarray terpendek atau 0
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ A[i] ≤ 10^9
 *                 1 ≤ S ≤ 2 × 10^14
 *
 * Sample Input 1:        Sample Output 1:
 * 6 7                    2
 * 2 1 5 2 3 2
 *
 * Sample Input 2:        Sample Output 2:
 * 5 11                   3
 * 1 2 3 4 5
 *
 * Sample Input 3:        Sample Output 3:
 * 4 100                  0
 * 1 2 3 4
 *
 * NOTE Sample 1: subarray [5,2] memiliki sum=7 (>=7) dengan panjang 2.
 * NOTE Sample 2: subarray [3,4,5] memiliki sum=12 (>=11) panjang 3.
 *                Atau [4,5] sum=9 (<11) tidak valid.
 * NOTE Sample 3: total sum = 10 < 100, mustahil.
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

    // TODO: Implementasi variable-size sliding window (shortest)
    // Hint:
    // int L = 0;
    // int ans = INT_MAX;
    // ll sum = 0;
    // for (int R = 0; R < n; R++) {
    //     sum += A[R];
    //     while (sum >= S) {
    //         ans = min(ans, R - L + 1);
    //         sum -= A[L];
    //         L++;
    //     }
    // }
    // cout << (ans == INT_MAX ? 0 : ans);

    return 0;
}
