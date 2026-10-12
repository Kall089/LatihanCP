/*
 * Day 20 — Sliding Window
 * File  : tugas_08.cpp
 * Topik : Maximum Erasure Value (Longest Unique Subarray Sum)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan positif.
 * Cari subarray kontinu dengan SEMUA elemen unik (distinct) yang
 * memiliki SUM TERBESAR. Output sum tersebut.
 *
 * Pendekatan: variable-size sliding window dengan unordered_set
 * atau frequency map. Saat A[R] sudah ada, shrink L sampai unique kembali.
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan positif
 * Output format : sum maksimum (long long)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 6                      17
 * 4 2 4 5 6 0
 *
 * Sample Input 2:        Sample Output 2:
 * 5                      8
 * 5 2 1 2 5 (note: should be 5 elements: 5,2,1,2,5)
 *
 * NOTE Sample 1: subarray [2,4,5,6] sum=17, semua unik. Atau [4,5,6,0]=15.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sliding window + set/map
    // Hint:
    // unordered_set<int> seen;
    // int L = 0; ll sum = 0, ans = 0;
    // for (int R = 0; R < n; R++) {
    //     while (seen.count(A[R])) {
    //         seen.erase(A[L]);
    //         sum -= A[L];
    //         L++;
    //     }
    //     seen.insert(A[R]);
    //     sum += A[R];
    //     ans = max(ans, sum);
    // }

    return 0;
}
