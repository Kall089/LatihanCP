/*
 * Day 6 — STL Algorithms
 * File  : solution_4.cpp
 * Topik : accumulate & Reduction Operations
 * -----------------------------------------------
 * Hitung: (1) sum array, (2) product array mod 1e9+7, (3) jumlah elemen genap, (4) max elemen.
 *
 * Input format  : Baris 1: n
Baris 2: n bilangan bulat positif
 * Output format : 4 baris: sum, product mod 1e9+7, count_even, max
 * Constraints   : 1 ≤ n ≤ 10^5, 1 ≤ A[i] ≤ 10^4
 *
 * Sample Input 1:
 * 5
 * 1 2 3 4 5
 *
 * Sample Output 1:
 * 15
 * 120
 * 2
 * 5
 *
 * Sample Input 2:
 * 4
 * 2 4 6 8
 *
 * Sample Output 2:
 * 20
 * 384
 * 4
 * 8
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MOD = 1e9 + 7;
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    ll sum = accumulate(A.begin(), A.end(), 0LL);
    ll prod = accumulate(A.begin(), A.end(), 1LL,
                         [&](ll acc, int x)
                         { return acc * x % MOD; });
    int even = count_if(A.begin(), A.end(), [](int x)
                        { return x % 2 == 0; });
    int mx = *max_element(A.begin(), A.end());

    cout << sum << "\n"
         << prod << "\n"
         << even << "\n"
         << mx << "\n";
    return 0;
}
