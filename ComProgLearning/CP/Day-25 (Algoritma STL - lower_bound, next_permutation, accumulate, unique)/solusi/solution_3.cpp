/*
 * Day 6 — STL Algorithms
 * File  : solution_3.cpp
 * Topik : next_permutation — Generate All Permutations
 * -----------------------------------------------
 * Generate semua permutasi dari array, cetak dalam urutan lexicographic. Gunakan next_permutation.
 *
 * Input format  : Baris 1: n
Baris 2: n bilangan (distinct)
 * Output format : Semua permutasi dalam urutan lexicographic, satu per baris
 * Constraints   : 1 ≤ n ≤ 8, elemen distinct
 *
 * Sample Input 1:
 * 3
 * 1 2 3
 *
 * Sample Output 1:
 * 1 2 3
 * 1 3 2
 * 2 1 3
 * 2 3 1
 * 3 1 2
 * 3 2 1
 *
 * Sample Input 2:
 * 2
 * 2 1
 *
 * Sample Output 2:
 * 1 2
 * 2 1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    sort(A.begin(), A.end());
    do {
        for (int i = 0; i < n; i++) cout << A[i] << "\n"[i==n-1];
    } while (next_permutation(A.begin(), A.end()));

    return 0;
}
