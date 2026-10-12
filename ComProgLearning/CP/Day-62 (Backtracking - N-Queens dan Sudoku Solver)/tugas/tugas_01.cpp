/*
 * Day 12 — Backtracking
 * File  : tugas_01.cpp
 * Topik : Generate All Binary Strings of Length N
 * Level : Easy
 * -----------------------------------------------
 * Cetak semua string biner (0/1) panjang n dalam urutan lexicographic.
 *
 * Input : Satu bilangan n
 * Output: Semua string biner
 * Constraints: 1 ≤ n ≤ 20
 *
 * Sample Input:
 * 2
 *
 * Sample Output:
 * 00
 * 01
 * 10
 * 11
 */

#include <bits/stdc++.h>
using namespace std;

void backtracking(int n, string &current)
{
    if (current.length() == n)
    {
        cout << current << endl;
        return;
    }

    for (char x : {'0', '1'})
    {
        current.push_back(x);
        backtracking(n, current);
        current.pop_back();
    }
}

int main()
{
    int n;
    cin >> n;

    string current = "";

    backtracking(n, current);
}