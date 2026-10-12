/*
 * Day 12 — Backtracking
 * File  : tugas_02.cpp
 * Topik : Generate Parentheses
 * Level : Easy
 * -----------------------------------------------
 * Generate semua kombinasi valid dari n pasang kurung buka-tutup.
 *
 * Input : Satu bilangan n
 * Output: Semua kombinasi valid sorted
 * Constraints: 1 ≤ n ≤ 8
 *
 * Sample Input:
 * 3
 *
 * Sample Output:
 * ((()))
 * (()())
 * (())()
 * ()(())
 * ()()()
 */

#include <bits/stdc++.h>
using namespace std;

void backtracking(int n, int open, int close, string &current)
{
    if (current.length() == n * 2)
    {
        cout << current << endl;
        return;
    }

    if (open < n)
    {
        current.push_back('(');
        backtracking(n, open + 1, close, current);
        current.pop_back();
    }

    if (close < open)
    {
        current.push_back(')');
        backtracking(n, open, close + 1, current);
        current.pop_back();
    }
}

int main()
{
    int n;
    cin >> n;

    string current;

    backtracking(n, 0, 0, current);
}