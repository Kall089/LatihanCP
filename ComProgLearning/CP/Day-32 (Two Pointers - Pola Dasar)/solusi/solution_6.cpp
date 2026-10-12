/*
 * Day 19 — Two Pointers
 * File  : solution_6.cpp
 * Topik : Merge Two Sorted Arrays — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Two Independent Pointers
 *
 * Idea:
 *   - i = pointer untuk A (0..n-1)
 *   - j = pointer untuk B (0..m-1)
 *   - Selalu ambil elemen yang lebih kecil dari kedua pointer
 *   - Advance pointer dari array yang diambil elemennya
 *   - Setelah salah satu array habis, append sisa array yang lain
 *
 * Correctness:
 *   Setiap langkah kita menempatkan elemen terkecil berikutnya
 *   ke dalam hasil. Karena A dan B sudah sorted, elemen minimum
 *   global selanjutnya pasti ada di A[i] atau B[j].
 *
 * Complexity: O(n+m) time, O(n+m) space
 *
 * Verifikasi sample:
 *   Sample 1: A=[1,3,5], B=[2,4,6]
 *     i=0,j=0: 1<2 → ambil 1, i++
 *     i=1,j=0: 3>2 → ambil 2, j++
 *     i=1,j=1: 3<4 → ambil 3, i++
 *     i=2,j=1: 5>4 → ambil 4, j++
 *     i=2,j=2: 5<6 → ambil 5, i++
 *     i=n, sisa B=[6] → ambil 6
 *     Output: 1 2 3 4 5 6 ✓
 *
 *   Sample 2: A=[1,3,7,9], B=[2,5]
 *     Output: 1 2 3 5 7 9 ✓
 *
 *   Sample 3: A=[1,2,3], B=[]
 *     j=m dari awal, loop tidak jalan
 *     Sisa A: 1 2 3
 *     Output: 1 2 3 ✓
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;

    vector<int> res;
    res.reserve(n + m);

    int i = 0, j = 0;

    // Merge: selalu ambil yang lebih kecil
    while (i < n && j < m) {
        if (A[i] <= B[j]) {
            res.push_back(A[i++]);
        } else {
            res.push_back(B[j++]);
        }
    }

    // Append sisa A (jika B sudah habis)
    while (i < n) res.push_back(A[i++]);

    // Append sisa B (jika A sudah habis)
    while (j < m) res.push_back(B[j++]);

    // Output
    for (int k = 0; k < (int)res.size(); k++) {
        cout << res[k];
        if (k < (int)res.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
