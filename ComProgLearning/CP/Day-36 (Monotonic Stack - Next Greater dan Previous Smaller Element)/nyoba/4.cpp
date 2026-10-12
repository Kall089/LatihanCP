/*
============================================================
📋 TUGAS 04: Harga Turun Berikutnya (Next Smaller)
============================================================
Source: Original
Difficulty: Medium
Topics: monotonic stack, next smaller element

PROBLEM:
Diberikan N harga barang berurutan. Untuk setiap barang, cari HARGA
barang PERTAMA SETELAHNYA yang harganya LEBIH MURAH.
Jika tidak ada, cetak -1.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan harga[i]

OUTPUT FORMAT:
- Satu baris berisi N bilangan dipisah spasi

CONSTRAINTS:
- 1 ≤ N ≤ 2*10^5
- 1 ≤ harga[i] ≤ 10^9

SAMPLE INPUT 1:
6
4 8 5 2 25 6

SAMPLE OUTPUT 1:
2 5 2 -1 6 -1

SAMPLE INPUT 2:
5
5 4 3 2 1

SAMPLE OUTPUT 2:
4 3 2 1 -1

NOTE: Loop harus berjalan MUNDUR dari kanan ke kiri.
      Sample 2 menurun terus, jadi tiap barang langsung menemukan
      tetangga kanannya sebagai jawaban.
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
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            hasil[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    for (int x : hasil)
    {
        cout << x << " ";
    }
}