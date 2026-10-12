/*
 * Day 6 — STL Algorithms
 * File  : exercise_2.cpp
 * Topik : Binary Search — lower_bound & upper_bound
 * -----------------------------------------------
 * Untuk array sorted, jawab q query:
 *   (1) jumlah elemen == x
 *   (2) index pertama >= x
 *   (3) index pertama > x
 *
 * Input format  : Baris 1: n q
 *                 Baris 2: n bilangan sorted ascending
 *                 Baris 3..q+2: satu bilangan x per query
 * Output format : Per query: count first_geq first_greater
 * Constraints   : 1 ≤ n,q ≤ 10^5, 1 ≤ A[i],x ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 6 3                  2 1 3
 * 1 2 2 3 4 4          1 3 4
 * 2                    0 6 6
 * 3
 * 5
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    while (m--)
    {
        int x;
        cin >> x;

        auto lo = lower_bound(arr.begin(), arr.end(), x);
        auto hi = upper_bound(arr.begin(), arr.end(), x);

        int count = (hi - lo);
        int first_geq = (lo - arr.begin());
        int first_greater = (hi - arr.begin());

        cout << count << " " << first_geq << " " << first_greater;
    }
}