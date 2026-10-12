/*
 * Day 6 — STL Algorithms
 * File  : solution_1.cpp
 * Topik : Sort — Basic & Custom Comparator
 * -----------------------------------------------
 * Sort array integer ascending, kemudian sort array pasangan (nilai, index) descending by nilai.
 *
 * Input format  : Baris 1: n
Baris 2: n bilangan bulat
 * Output format : Baris 1: array sorted ascending
Baris 2: array sorted descending
 * Constraints   : 1 ≤ n ≤ 10^5, -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:
 * 5
 * 3 1 4 1 5
 *
 * Sample Output 1:
 * 1 1 3 4 5
 * 5 4 3 1 1
 *
 * Sample Input 2:
 * 4
 * 9 2 7 4
 *
 * Sample Output 2:
 * 2 4 7 9
 * 9 7 4 2
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
    for (int i = 0; i < n; i++) cout << A[i] << "\n"[i==n-1];

    sort(A.begin(), A.end(), greater<int>());
    for (int i = 0; i < n; i++) cout << A[i] << "\n"[i==n-1];

    return 0;
}
