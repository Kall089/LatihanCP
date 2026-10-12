/*
============================================================
📋 TUGAS 03: Batas Kiri Lembah (Previous Smaller)
============================================================
Source: Original
Difficulty: Medium
Topics: monotonic stack, previous smaller element

PROBLEM:
Diberikan N tinggi batang. Untuk setiap batang, cari INDEKS batang
TERDEKAT DI SEBELAH KIRI yang tingginya LEBIH KECIL.
Jika tidak ada, cetak -1.
Gunakan indeks berbasis 0.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan tinggi[i]

OUTPUT FORMAT:
- Satu baris berisi N bilangan dipisah spasi

CONSTRAINTS:
- 1 ≤ N ≤ 2*10^5
- 1 ≤ tinggi[i] ≤ 10^9

SAMPLE INPUT 1:
6
6 2 5 4 5 1

SAMPLE OUTPUT 1:
-1 -1 1 1 3 -1

SAMPLE INPUT 2:
5
4 4 4 4 4

SAMPLE OUTPUT 2:
-1 -1 -1 -1 -1

NOTE: Kali ini yang dicetak INDEKS, bukan nilai.
      Sample 2: tinggi yang SAMA tidak dihitung "lebih kecil".
      Soal ini adalah setengah dari Largest Rectangle in Histogram.
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
        while (!st.empty() && arr[st.top()] >= arr[i])
        {
            st.pop();
        }

        if (!st.empty())
        {
            hasil[i] = st.top();
        }
        st.push(i);
    }

    for (int x : hasil)
    {
        cout << x << " ";
    }
}