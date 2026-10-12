/*
============================================================
📋 TUGAS 6: Stack — Min Stack
============================================================
Source: LeetCode-style
Difficulty: Medium
Topics: stack, design

PROBLEM:
Implementasi stack yang support operasi getMin() dalam O(1).

Operasi:
- "push x": push x ke stack
- "pop": pop top element
- "top": cetak top element
- "min": cetak elemen minimum di stack saat ini

INPUT:
- Baris pertama: integer Q (jumlah operasi)
- Q baris berikutnya: operasi

OUTPUT:
- Untuk setiap "top" dan "min": cetak hasilnya

CONSTRAINTS:
- 1 ≤ Q ≤ 200,000
- -1,000,000,000 ≤ x ≤ 1,000,000,000
- pop/top/min dijamin dipanggil saat stack tidak kosong

SAMPLE INPUT:
8
push 5
push 3
push 7
min
pop
min
top
min

SAMPLE OUTPUT:
3
3
3
3

NOTE: Stack: [5,3,7]. Min=3. Pop 7. Stack: [5,3]. Min=3. Top=3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di
    int n;
    cin >> n;

    stack<pair<int, int>> st;

    while (n--)
    {
        string s;
        cin >> s;

        if (s == "push")
        {
            int x;
            cin >> x;

            if (st.empty())
            {
                st.push({x, x});
            }
            else
            {
                int min_curr = min(x, st.top().second);
                st.push({x, min_curr});
            }
        }
        else if (s == "min")
        {
            cout << st.top().second << endl;
        }
        else if (s == "pop")
        {
            st.pop();
        }
        else
        {
            cout << st.top().first << endl;
        }
    }
    // Hint: Maintain dua stack: satu biasa, satu track minimum.
    //       Atau simpan pair<value, current_min> di satu stack.

    return 0;
}
