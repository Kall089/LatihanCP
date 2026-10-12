/*
============================================================
📋 TUGAS 1: Stack — Reverse Array
============================================================
Source: Original
Difficulty: Easy
Topics: stack

PROBLEM:
Diberikan N bilangan. Cetak dalam urutan TERBALIK menggunakan stack.

INPUT:
- Baris pertama: integer N
- Baris kedua: N integer

OUTPUT:
- Satu baris: N integer dalam urutan terbalik

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000

SAMPLE INPUT:
5
1 2 3 4 5

SAMPLE OUTPUT:
5 4 3 2 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        st.push(x);
    }

    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}
