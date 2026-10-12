/*
============================================================
📋 TUGAS 04: House Robber II (Melingkar)
============================================================
Source: LC 213
Difficulty: Medium
Topics: dua kali jalan linear

PROBLEM:
Sama seperti Tugas 03, tetapi elemen pertama dan terakhir bertetangga.

INPUT FORMAT / OUTPUT FORMAT: sama
CONSTRAINTS: 1 <= N <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3                      3
2 3 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4                      4
1 2 3 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1                      5
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> dp(n, 0);
}