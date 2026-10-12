/*
 * Day 11 — Recursion Dasar
 * File  : exercise_1.cpp
 * Topik : Factorial Rekursif
 * -----------------------------------------------
 * Hitung n! (n faktorial) menggunakan rekursi.
 * Ingat: 0! = 1 (base case).
 *
 * Input format  : Satu bilangan n
 * Output format : Nilai n!
 * Constraints   : 0 ≤ n ≤ 20
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    120
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    1
 *
 * Sample Input 3:      Sample Output 3:
 * 10                   3628800
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Implementasikan fungsi factorial rekursif
// Ingat: factorial(0) = 1 (BASE CASE)
//        factorial(n) = n * factorial(n-1)
ll factorial(int n)
{
    if (n == 0)
    {
        return 1LL;
    }
    return n * factorial(n - 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    cout << factorial(n) << "\n";

    return 0;
}
