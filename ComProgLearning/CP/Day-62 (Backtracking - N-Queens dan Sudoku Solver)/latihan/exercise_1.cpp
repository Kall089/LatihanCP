/*
 * Day 12 — Backtracking
 * File  : exercise_1.cpp
 * Topik : Generate All Permutations
 * -----------------------------------------------
 * Generate semua permutasi dari bilangan 1..n secara backtracking (bukan next_permutation).
 *
 * Input format  : Satu bilangan n
 * Output format : Semua permutasi dalam urutan lexicographic, satu per baris
 * Constraints   : 1 ≤ n ≤ 8
 *
 * Sample Input 1:
 * 3
 *
 * Sample Output 1:
 * 1 2 3
 * 1 3 2
 * 2 1 3
 * 2 3 1
 * 3 1 2
 * 3 2 1
 *
 * Sample Input 2:
 * 2
 *
 * Sample Output 2:
 * 1 2
 * 2 1
 */

#include <bits/stdc++.h>
using namespace std;

// arr dipassing sebagai const reference (&) agar TIDAK dicopy berulang kali
void backtracking(const vector<int> &arr, vector<int> &perm, vector<bool> &used, int n)
{
    // Base case: jika ukuran permutasi sudah mencapai n
    if ((int)perm.size() == n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << perm[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (used[i])
            continue;

        used[i] = true;
        perm.push_back(arr[i]);

        backtracking(arr, perm, used, n);

        perm.pop_back(); // Backtrack
        used[i] = false;
    }
}

int main()
{
    // Optimasi I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<bool> used(n, false);
    vector<int> perm;

    backtracking(arr, perm, used, n);

    return 0;
}