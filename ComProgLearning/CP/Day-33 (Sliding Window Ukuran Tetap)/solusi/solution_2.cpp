/*
 * Day 20 — Sliding Window
 * File  : solution_2.cpp
 * Topik : First Negative Number in Every Window of Size K — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Sliding Window + Deque menyimpan INDEX elemen negatif
 *
 * Idea:
 *   - Deque menyimpan index dari elemen-elemen NEGATIF di dalam window.
 *   - Setelah scan i, dq.front() = index negatif paling kiri (jika ada).
 *   - Saat slide: pop_front index yang keluar window.
 *
 * Mengapa O(n)?
 *   - Setiap index di-push max 1 kali, di-pop max 1 kali → O(n) total.
 *
 * Verifikasi sample 1: A=[12,-1,-7,8,-15,30,16,28], K=3
 *   i=0: A[0]=12 ≥0, dq=[]; window belum penuh
 *   i=1: A[1]=-1, dq=[1]; window belum penuh
 *   i=2: A[2]=-7, dq=[1,2]; window penuh → A[1]=-1 ✓
 *   i=3: pop_front jika ≤ 0: dq.front()=1 > 0, no pop;
 *        A[3]=8 ≥0, dq=[1,2]; → A[1]=-1 ✓
 *   i=4: pop_front jika ≤ 1: dq.front()=1 ≤ 1, pop → dq=[2];
 *        A[4]=-15, dq=[2,4]; → A[2]=-7 ✓
 *   i=5: pop_front jika ≤ 2: dq.front()=2 ≤ 2, pop → dq=[4];
 *        A[5]=30 ≥0, dq=[4]; → A[4]=-15 ✓
 *   i=6: pop_front jika ≤ 3: 4 > 3, no pop;
 *        A[6]=16 ≥0; dq=[4]; → A[4]=-15 ✓
 *   i=7: pop_front jika ≤ 4: 4 ≤ 4, pop → dq=[];
 *        A[7]=28 ≥0, dq=[]; → 0 ✓
 *   Output: -1 -1 -7 -15 -15 0  ✓
 *
 * Complexity: O(n) time, O(K) space
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

    deque<int> dq;  // simpan INDEX elemen negatif

    for (int i = 0; i < n; i++) {
        // Buang index dari front yang keluar window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // Tambah index sekarang jika negatif
        if (A[i] < 0) dq.push_back(i);

        // Output saat window penuh
        if (i >= k - 1) {
            if (dq.empty()) cout << 0;
            else            cout << A[dq.front()];
            cout << (i == n - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
