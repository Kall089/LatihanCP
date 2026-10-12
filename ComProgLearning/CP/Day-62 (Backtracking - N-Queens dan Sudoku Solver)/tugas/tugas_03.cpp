/*
 * Day 12 — Backtracking
 * File  : tugas_03.cpp
 * Topik : Phone Number Letter Combinations
 * Level : Easy
 * -----------------------------------------------
 * Diberikan digit 2-9, hasilkan semua huruf yang mungkin (keypad HP).
 *
 * Input : String digit (2-9)
 * Output: Semua kombinasi huruf
 * Constraints: 1 ≤ |digits| ≤ 4
 *
 * Sample Input:
 * 23
 *
 * Sample Output:
 * ad ae af bd be bf cd ce cf
 */

#include <bits/stdc++.h>
using namespace std;

void backtracking(int idx, string &current, vector<string> mp, string s)
{
    if (idx == s.size())
    {
        cout << current << " ";
        return;
    }

    for (char ch : mp[s[idx] - '0'])
    {
        current.push_back(ch);
        backtracking(idx + 1, current, mp, s);
        current.pop_back();
    }
}

int main()
{
    string s;
    cin >> s;
    string current;

    vector<string> mp = {"", "", "abc", "def", "hij", "klm", "nop", "qrs", "tuv", "wxyz"};

    backtracking(0, current, mp, s);
}
