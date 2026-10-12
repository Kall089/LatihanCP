/*
 * Day 12 — Backtracking
 * File  : solution_2.cpp
 * Topik : Generate All Subsets (Power Set)
 * -----------------------------------------------
 * Generate semua subset dari bilangan 1..n. Cetak dalam urutan lexicographic (subset kosong juga).
 *
 * Input format  : Satu bilangan n
 * Output format : Semua subset, satu per baris (subset kosong = baris kosong)
 * Constraints   : 1 ≤ n ≤ 15
 *
 * Sample Input 1:
 * 3
 *
 * Sample Output 1:
 *
 * 1
 * 1 2
 * 1 2 3
 * 1 3
 * 2
 * 2 3
 * 3
 *
 * Sample Input 2:
 * 2
 *
 * Sample Output 2:
 *
 * 1
 * 1 2
 * 2
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void backtrack(int start, vector<int> &subset, int n)
{
    for (int i = 0; i < (int)subset.size(); i++)
        cout << subset[i] << " ";
    cout << endl;

    for (int i = start; i <= n; i++)
    {
        subset.push_back(i);
        backtrack(i + 1, subset, n);
        subset.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    vector<int> subset;

    cin >> n;
    backtrack(1, subset, n);
    return 0;
}
