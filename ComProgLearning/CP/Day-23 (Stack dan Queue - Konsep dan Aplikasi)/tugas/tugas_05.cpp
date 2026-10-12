/*
============================================================
📋 TUGAS 5: Deque — Palindrome Check
============================================================
Source: Original
Difficulty: Easy
Topics: deque, two-sided comparison

PROBLEM:
Diberikan string. Cek apakah palindrome menggunakan DEQUE.
Bandingkan front dan back, pop keduanya, ulangi.

INPUT:
- Satu baris: string s (huruf kecil)

OUTPUT:
- "YES" jika palindrome, "NO" jika bukan

CONSTRAINTS:
- 1 ≤ |s| ≤ 200,000

SAMPLE INPUT:
racecar

SAMPLE OUTPUT:
YES

SAMPLE INPUT 2:
hello

SAMPLE OUTPUT 2:
NO
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    deque<char> dq;

    for (int x : s)
    {
        dq.push_back(x);
    }

    bool valid = true;

    while (dq.size() > 1)
    {
        if (dq.front() != dq.back())
        {
            valid = false;
            break;
        }
        dq.pop_back();
        dq.pop_front();
    }

    if (valid)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
