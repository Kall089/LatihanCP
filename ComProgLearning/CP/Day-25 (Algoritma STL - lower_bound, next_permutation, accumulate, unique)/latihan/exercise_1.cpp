/*
 * Day 6 — STL Algorithms
 * File  : exercise_1.cpp
 * Topik : Sort — Basic & Custom Comparator
 * -----------------------------------------------
 * Sort array integer ascending, kemudian descending.
 *
 * Input format  : Baris 1: n
 *                 Baris 2: n bilangan bulat
 * Output format : Baris 1: array sorted ascending
 *                 Baris 2: array sorted descending
 * Constraints   : 1 ≤ n ≤ 10^5, -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    1 1 3 4 5
 * 3 1 4 1 5            5 4 3 1 1
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    2 4 7 9
 * 9 2 7 4              9 7 4 2
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

    // TODO 1: Sort ascending (gunakan std::sort)
    // sort(A.begin(), A.end());

    // Print ascending
    for (int i = 0; i < n; i++) cout << A[i] << " \n"[i==n-1];

    // TODO 2: Sort descending (gunakan custom comparator atau greater<int>)
    // sort(A.begin(), A.end(), greater<int>());

    // Print descending
    for (int i = 0; i < n; i++) cout << A[i] << " \n"[i==n-1];

    return 0;
}
