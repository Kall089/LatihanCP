/*
 * Day 20 — Sliding Window
 * File  : solution_5.cpp
 * Topik : Sliding Window Maximum (Monotonic Deque) — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Monotonic Deque O(n)
 *
 * Idea:
 *   Deque menyimpan INDEX dengan invariant:
 *     - Semua index berada di window saat ini [i-k+1, i]
 *     - A[dq.front()] >= A[dq[1]] >= ... >= A[dq.back()] (decreasing)
 *
 *   Saat scan ke i:
 *     1. Buang dari FRONT: index yang keluar window (dq.front() <= i - k)
 *     2. Buang dari BACK: index dengan A[idx] <= A[i]
 *        (mereka tidak akan pernah jadi max selama A[i] ada)
 *     3. push_back(i)
 *     4. Saat i >= k-1: A[dq.front()] adalah maksimum window
 *
 * Mengapa O(n)?
 *   Setiap index di-push tepat 1 kali dan di-pop maksimal 1 kali.
 *   Total operasi ≤ 2n = O(n).
 *
 * Mengapa pop saat A[back] <= A[i]?
 *   Misal di belakang ada index j dengan A[j] <= A[i].
 *   Selama i masih di window, j tidak bisa jadi max (karena ada A[i] >= A[j]).
 *   Setelah i keluar, j juga sudah keluar dulu (karena j < i).
 *   Jadi j tidak akan PERNAH jadi max → bisa dibuang.
 *
 * Verifikasi sample 1: A=[1,3,-1,-3,5,3,6,7], K=3
 *   i=0: dq=[0]; window belum penuh
 *   i=1: A[0]=1 <= A[1]=3 → pop; dq=[1]; window belum penuh
 *   i=2: dq=[1,2]; output A[1]=3 ✓
 *   i=3: dq.front()=1 > 0, no front-pop; A[2]=-1 > A[3]=-3, no back-pop;
 *        dq=[1,2,3]; output A[1]=3 ✓
 *   i=4: front 1 <= 1, pop → dq=[2,3]; A[3]=-3<=5,pop;A[2]=-1<=5,pop;
 *        dq=[4]; output A[4]=5 ✓
 *   i=5: dq=[4,5]; output A[4]=5 ✓
 *   i=6: A[5]=3<=6,pop; A[4]=5<=6,pop; dq=[6]; output A[6]=6 ✓
 *   i=7: A[6]=6<=7,pop; dq=[7]; output A[7]=7 ✓
 *   Output: 3 3 5 5 6 7 ✓
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

    deque<int> dq;   // simpan INDEX, A[idx] decreasing dari front

    for (int i = 0; i < n; i++) {
        // 1. Buang index yang keluar window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // 2. Buang index dari belakang yang nilainya ≤ A[i]
        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();

        // 3. Tambah index sekarang
        dq.push_back(i);

        // 4. Output max ketika window penuh
        if (i >= k - 1) {
            cout << A[dq.front()];
            cout << (i == n - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
