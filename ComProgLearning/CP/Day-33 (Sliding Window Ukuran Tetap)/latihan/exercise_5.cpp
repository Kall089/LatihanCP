/*
 * Day 20 — Sliding Window
 * File  : exercise_5.cpp
 * Topik : Sliding Window Maximum (Monotonic Deque)
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan dan integer K.
 * Untuk setiap window kontinu berukuran K, cetak nilai MAKSIMUM di window.
 *
 * Total output: (N - K + 1) bilangan dipisah spasi.
 *
 * Pendekatan MONOTONIC DEQUE O(n):
 *   - Deque menyimpan INDEX dengan nilai A[idx] DECREASING dari front
 *   - Saat scan i:
 *     1. Buang index dari front yang keluar window (dq.front() <= i - K)
 *     2. Buang index dari back yang nilai-nya <= A[i]
 *     3. push_back(i)
 *     4. Saat i >= K-1 → output A[dq.front()]
 *
 * Pre-syarat invariant: deque selalu decreasing → front = max window.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan
 * Output format : (N-K+1) bilangan, dipisah spasi
 * Constraints   : 1 ≤ K ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 8 3                    3 3 5 5 6 7
 * 1 3 -1 -3 5 3 6 7
 *
 * Sample Input 2:        Sample Output 2:
 * 5 2                    7 7 5 8
 * 4 7 5 3 8
 *
 * Sample Input 3:        Sample Output 3:
 * 6 6                    9
 * 1 5 9 2 7 3
 *
 * NOTE Sample 1:
 *   [1,3,-1] → max=3
 *   [3,-1,-3]→ max=3
 *   [-1,-3,5]→ max=5
 *   [-3,5,3] → max=5
 *   [5,3,6]  → max=6
 *   [3,6,7]  → max=7
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    // TODO: Implementasi sliding window maximum dengan monotonic deque
    // Hint:
    // deque<int> dq;  // simpan INDEX
    // for (int i = 0; i < n; i++) {
    //     // 1. Buang front yang out of window
    //     while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    //     // 2. Buang back yang nilainya <= A[i]
    //     while (!dq.empty() && A[dq.back()] <= A[i]) dq.pop_back();
    //     // 3. Push index sekarang
    //     dq.push_back(i);
    //     // 4. Output ketika window penuh
    //     if (i >= k - 1) {
    //         cout << A[dq.front()];
    //         cout << (i == n - 1 ? '\n' : ' ');
    //     }
    // }

    return 0;
}
