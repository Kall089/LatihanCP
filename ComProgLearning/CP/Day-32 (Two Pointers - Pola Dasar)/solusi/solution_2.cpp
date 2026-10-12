/*
 * Day 19 — Two Pointers
 * File  : solution_2.cpp
 * Topik : Remove Duplicates In-Place — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Slow-Fast Two Pointers (Same Direction)
 *
 * Idea:
 *   - slow = posisi penulisan (write pointer), mulai dari 0
 *   - fast iterasi semua elemen dari 1 sampai n-1
 *   - Jika A[fast] != A[slow]: elemen unik baru
 *     → tulis ke A[++slow]
 *   - Jika A[fast] == A[slow]: duplikat → skip (slow tidak maju)
 *
 * Invariant: A[0..slow] selalu berisi elemen unik terurut
 *
 * Complexity: O(n) time, O(1) space
 *
 * Verifikasi sample:
 *   Sample 1: A=[1,1,2,3,3,3,4]
 *     slow=0: A[0]=1 (init)
 *     fast=1: A[1]=1==A[0]=1 → skip
 *     fast=2: A[2]=2!=A[0]=1 → A[++slow=1]=2
 *     fast=3: A[3]=3!=A[1]=2 → A[++slow=2]=3
 *     fast=4: A[4]=3==A[2]=3 → skip
 *     fast=5: A[5]=3==A[2]=3 → skip
 *     fast=6: A[6]=4!=A[2]=3 → A[++slow=3]=4
 *     len=4, output: "4\n1 2 3 4" ✓
 *
 *   Sample 2: A=[1,2,2,3,3]
 *     Result: [1,2,3], len=3 ✓
 *
 *   Sample 3: A=[5]
 *     len=1, output: "1\n5" ✓
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    if (n == 0) {
        cout << "0\n\n";
        return 0;
    }

    // Slow-Fast Two Pointers
    int slow = 0;
    for (int fast = 1; fast < n; fast++) {
        if (A[fast] != A[slow]) {
            // Elemen unik baru: tulis ke posisi slow berikutnya
            A[++slow] = A[fast];
        }
        // Jika duplikat: fast maju, slow diam
    }

    int len = slow + 1;

    cout << len << "\n";
    for (int i = 0; i < len; i++) {
        cout << A[i];
        if (i < len - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
