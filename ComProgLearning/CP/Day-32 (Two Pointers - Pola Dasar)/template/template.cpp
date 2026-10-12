/*
 * Day 19 — Two Pointers
 * Template C++ dengan pola two pointers
 *
 * Pilih pola yang sesuai dengan problem, hapus yang tidak diperlukan.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ──────────────────────────────────────────────────────────────────
// POLA 1: OPPOSITE DIRECTION (Sorted Array)
// Pre-condition: array harus sorted (untuk pair sum)
// Use for: pair sum = target, palindrome, container water
// ──────────────────────────────────────────────────────────────────
//
// int L = 0, R = n - 1;
// while (L < R) {
//     if (kondisi_terpenuhi) {
//         // proses hasil
//         break;  // atau L++; R--;
//     } else if (perlu_nilai_lebih_besar) {
//         L++;    // geser kiri ke kanan (nilai naik karena sorted)
//     } else {
//         R--;    // geser kanan ke kiri (nilai turun karena sorted)
//     }
// }

// ──────────────────────────────────────────────────────────────────
// POLA 2: SAME DIRECTION — SLOW-FAST
// Use for: remove duplicates, move zeros, filter elements in-place
// ──────────────────────────────────────────────────────────────────
//
// int slow = 0;
// for (int fast = 0; fast < n; fast++) {
//     if (valid(A[fast])) {
//         A[slow] = A[fast];
//         slow++;
//     }
//     // Jika tidak valid: fast maju, slow diam
// }
// // slow = jumlah elemen valid setelah filter

// ──────────────────────────────────────────────────────────────────
// POLA 3: SLIDING WINDOW (Subarray dengan Constraint)
// Use for: longest subarray sum <= K, min window substring
// Pre-condition: elemen non-negatif untuk sum constraint
// ──────────────────────────────────────────────────────────────────
//
// int L = 0, ans = 0;
// ll sum = 0;
// for (int R = 0; R < n; R++) {
//     sum += A[R];                    // expand window ke kanan
//     while (sum > K && L <= R) {     // shrink dari kiri saat violated
//         sum -= A[L];
//         L++;
//     }
//     ans = max(ans, R - L + 1);      // update jawaban
// }

// ──────────────────────────────────────────────────────────────────
// POLA 4: MERGE TWO SORTED ARRAYS
// Use for: merge sort step, find common elements, sorted union
// Pre-condition: kedua array harus sorted
// ──────────────────────────────────────────────────────────────────
//
// int i = 0, j = 0;
// vector<int> res;
// while (i < n && j < m) {
//     if (A[i] <= B[j]) {
//         res.push_back(A[i++]);   // ambil dari A
//     } else {
//         res.push_back(B[j++]);   // ambil dari B
//     }
// }
// while (i < n) res.push_back(A[i++]);   // sisa A
// while (j < m) res.push_back(B[j++]);   // sisa B

// ──────────────────────────────────────────────────────────────────
// POLA 5: DUTCH NATIONAL FLAG (3-Way Partition)
// Use for: sort 0/1/2, 3-way partition
// ──────────────────────────────────────────────────────────────────
//
// int low = 0, mid = 0, high = n - 1;
// while (mid <= high) {
//     if (A[mid] == 0) {
//         swap(A[low], A[mid]);
//         low++;
//         mid++;
//     } else if (A[mid] == 1) {
//         mid++;
//     } else { // A[mid] == 2
//         swap(A[mid], A[high]);
//         high--;
//         // JANGAN mid++! Elemen baru di mid belum diproses
//     }
// }

// ──────────────────────────────────────────────────────────────────
// POLA 6: THREE SUM (Fix outer + Two Pointer inner)
// Use for: triplet sum problems
// Pre-condition: array harus sorted
// ──────────────────────────────────────────────────────────────────
//
// sort(A.begin(), A.end());
// for (int i = 0; i < n - 2; i++) {
//     if (i > 0 && A[i] == A[i-1]) continue;  // skip duplikat outer
//     int L = i + 1, R = n - 1;
//     while (L < R) {
//         int s = A[i] + A[L] + A[R];
//         if (s == target) {
//             // found triplet
//             while (L < R && A[L] == A[L+1]) L++;  // skip dup L
//             while (L < R && A[R] == A[R-1]) R--;  // skip dup R
//             L++; R--;
//         } else if (s < target) L++;
//         else R--;
//     }
// }

// ──────────────────────────────────────────────────────────────────
// HELPER: Check palindrome dengan two pointers
// ──────────────────────────────────────────────────────────────────
//
// bool isPalindrome(const string& s, int L, int R) {
//     while (L < R) {
//         if (s[L] != s[R]) return false;
//         L++; R--;
//     }
//     return true;
// }

// ──────────────────────────────────────────────────────────────────
// MAIN
// ──────────────────────────────────────────────────────────────────

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Baca input
    int n;
    cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    // Pilih dan implementasikan pola yang sesuai di sini

    return 0;
}
