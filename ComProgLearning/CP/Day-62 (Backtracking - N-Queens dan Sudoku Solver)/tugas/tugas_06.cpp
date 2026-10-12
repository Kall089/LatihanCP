/*
 * Day 12 — Backtracking
 * File  : tugas_06.cpp
 * Topik : Permutations with Duplicates
 * Level : Medium
 * -----------------------------------------------
 * Generate semua permutasi unik dari array yang mungkin mengandung duplikat.
 *
 * Input : Baris 1: n
Baris 2: n bilangan
 * Output: Semua permutasi unik sorted
 * Constraints: 1 ≤ n ≤ 8
 *
 * Sample Input:
 * 3
 * 1 1 2
 *
 * Sample Output:
 * 1 1 2
 * 1 2 1
 * 2 1 1
 */

#include <bits/stdc++.h>
using namespace std;

void backtracking(vector<int> &count, vector<vector<int>> &result, vector<int> arr, vector<bool> &visited)
{
    if (count.size() == arr.size())
    {
        result.push_back(count);
        return;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        if (visited[i])
            continue;

        if (i > 0 && arr[i] == arr[i - 1] && !visited[i - 1])
            continue;

        visited[i] = true;
        count.push_back(arr[i]);
        backtracking(count, result, arr, visited);
        count.pop_back();
        visited[i] = false;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr;
    vector<int> count;

    vector<bool> visited(n, false);

    while (n--)
    {
        int u;
        cin >> u;
        arr.push_back(u);
    }
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;

    backtracking(count, result, arr, visited);

    for (vector<int> x : result)
    {
        for (int y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }
}
