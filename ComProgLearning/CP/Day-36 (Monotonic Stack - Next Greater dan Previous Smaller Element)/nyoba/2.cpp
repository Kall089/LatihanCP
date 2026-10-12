/*
============================================================
📋 TUGAS 02: Rekor Tertinggi Terdekat (Previous Greater)
============================================================
Source: Original
Difficulty: Easy
Topics: monotonic stack, previous greater element

PROBLEM:
Diberikan N skor pertandingan berurutan. Untuk setiap pertandingan,
cari SKOR pertandingan TERDEKAT SEBELUMNYA yang skornya LEBIH BESAR.
Jika tidak ada, cetak -1.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan skor[i]

OUTPUT FORMAT:
- Satu baris berisi N bilangan dipisah spasi

CONSTRAINTS:
- 1 ≤ N ≤ 2*10^5
- 1 ≤ skor[i] ≤ 10^9

SAMPLE INPUT 1:
6
5 3 8 2 7 1

SAMPLE OUTPUT 1:
-1 5 -1 8 8 7

SAMPLE INPUT 2:
5
1 2 3 4 5

SAMPLE OUTPUT 2:
-1 -1 -1 -1 -1

NOTE: Yang dicetak adalah NILAI-nya, bukan jarak.
      Sample 2 menaik terus, jadi tidak ada yang punya pendahulu lebih besar.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    stack<int> st;
    vector<int> hasil(n, -1);

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] <= arr[i])
        {
            st.pop();
        }
        if (!st.empty())
            hasil[i] = arr[st.top()];
        st.push(i);
    }

    for (int x : hasil)
    {
        cout << x << " ";
    }
}
