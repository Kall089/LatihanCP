/*
 * Day 6 — STL Algorithms
 * File  : exercise_3.cpp
 * Topik : next_permutation — Generate All Permutations
 * -----------------------------------------------
 * Generate semua permutasi dari array, cetak dalam urutan lexicographic.
 *
 * Input format  : Baris 1: n
 *                 Baris 2: n bilangan (distinct)
 * Output format : Semua permutasi dalam urutan lexicographic, satu per baris
 * Constraints   : 1 ≤ n ≤ 8, elemen distinct
 *
 * Sample Input 1:      Sample Output 1:
 * 3                    1 2 3
 * 1 2 3                1 3 2
 *                      2 1 3
 *                      2 3 1
 *                      3 1 2
 *                      3 2 1
 *
 * Sample Input 2:      Sample Output 2:
 * 2                    1 2
 * 2 1                  2 1
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    do
    {
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    } while (next_permutation(arr.begin(), arr.end()));
}
