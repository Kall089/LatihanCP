/*
 * Day 16 — Custom Comparator
 * File  : exercise_5.cpp
 * Topik : Index Sort
 * -----------------------------------------------
 * Sort indices sebuah array sehingga A[idx[0]] ≤ A[idx[1]] ≤ ... ≤ A[idx[n-1]]. Output index (0-indexed).
 *
 * Input format  : Baris 1: n
Baris 2: n bilangan
 * Output format : Indices setelah sort by value
 * Constraints   : 1 ≤ n ≤ 10^5, -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    1 3 0 4 2
 * 30 10 50 20 40
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

    // TODO: Buat array index [0,1,...,n-1]
    // vector<int> idx(n);
    // iota(idx.begin(), idx.end(), 0);

    // TODO: Sort idx berdasarkan A[idx[i]] menggunakan lambda
    // sort(idx.begin(), idx.end(),
    //     [&A](int i, int j){ return A[i] < A[j]; });

    vector<int> idx(n); // placeholder
    for (int i = 0; i < n; i++) cout << idx[i] << " \n"[i==n-1];

    return 0;
}
