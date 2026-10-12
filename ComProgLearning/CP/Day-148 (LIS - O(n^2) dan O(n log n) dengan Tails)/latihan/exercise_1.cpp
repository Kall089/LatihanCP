#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)
 * Latihan 1: LIS Versi O(n^2)
 *
 * Diberi array N bilangan. Cetak panjang subsekuens naik KETAT terpanjang.
 * Wajib memakai pendekatan O(N^2) — versi cepat ada di Latihan 2.
 *
 * Batas: 1 <= N <= 5000, |a[i]| <= 10^9
 *
// Test Case 1:
// Input:
// 8
// 10 9 2 5 3 7 101 18
// Output:
// 4
// (mis. 2 3 7 18 atau 2 5 7 101)
//
// Test Case 2 (semua menurun):
// Input:
// 5
// 5 4 3 2 1
// Output:
// 1
//
// Test Case 3 (ada nilai negatif dan kembar):
// Input:
// 6
// -3 -3 0 -1 2 2
// Output:
// 3
// (mis. -3 0 2 atau -3 -1 2)
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    vector<int> dp(n, 1);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <)
    }
}