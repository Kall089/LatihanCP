/*
 * Day 6 — STL Algorithms
 * File  : exercise_4.cpp
 * Topik : accumulate & Reduction Operations
 * -----------------------------------------------
 * Hitung: (1) sum, (2) product mod 1e9+7, (3) jumlah elemen genap, (4) max elemen.
 *
 * Input format  : Baris 1: n
 *                 Baris 2: n bilangan bulat positif
 * Output format : 4 baris: sum, product mod 1e9+7, count_even, max
 * Constraints   : 1 ≤ n ≤ 10^5, 1 ≤ A[i] ≤ 10^4
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    15
 * 1 2 3 4 5            120
 *                      2
 *                      5
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    20
 * 2 4 6 8              384
 *                      4
 *                      8
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int mod = 1e9 + 7;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int sum = accumulate(arr.begin(), arr.end(), 0LL);
    int product = accumulate(arr.begin(), arr.end(),
                             1LL, [&](long long acc, int x)
                             { return acc * x % mod; });
    int even = count_if(arr.begin(), arr.end(), [&](int x)
                        { return x % 2 == 0; });
    int max_elem = *max_element(arr.begin(), arr.end());

    cout << sum << "\n"
         << product << "\n"
         << even << "\n"
         << max_elem;
}
