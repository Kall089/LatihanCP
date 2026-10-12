/*
 * Day 6 — STL Algorithms
 * File  : solution_2.cpp
 * Topik : Binary Search — lower_bound & upper_bound
 * -----------------------------------------------
 * Untuk array sorted, jawab q query: (1) jumlah elemen = x, (2) index pertama >= x, (3) index pertama > x.
 *
 * Input format  : Baris 1: n q
Baris 2: n bilangan sorted
Baris q berikutnya: x
 * Output format : Per query: count first_geq first_greater
 * Constraints   : 1 ≤ n,q ≤ 10^5, 1 ≤ x,A[i] ≤ 10^9
 *
 * Sample Input 1:
 * 6 3
 * 1 2 2 3 4 4
 * 2
 * 3
 * 5
 *
 * Sample Output 1:
 * 2 1 3
 * 1 3 4
 * 0 6 6
 *
 * Sample Input 2:
 * 5 2
 * 1 1 1 1 1
 * 1
 * 2
 *
 * Sample Output 2:
 * 5 0 5
 * 0 5 5
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    while (q--)
    {
        int x;
        cin >> x;
        auto lo = lower_bound(A.begin(), A.end(), x);
        auto hi = upper_bound(A.begin(), A.end(), x);
        int count = (int)(hi - lo);
        int first_geq = (int)(lo - A.begin());
        int first_greater = (int)(hi - A.begin());
        cout << count << " " << first_geq << " " << first_greater << "\n";
    }
    return 0;
}
