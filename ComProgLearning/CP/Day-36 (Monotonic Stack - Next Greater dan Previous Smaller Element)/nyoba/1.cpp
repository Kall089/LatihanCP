/*
============================================================
📋 TUGAS 01: Suhu Menghangat (Next Greater)
============================================================
Source: Original
Difficulty: Easy
Topics: monotonic stack, next greater element

PROBLEM:
Diberikan N suhu harian. Untuk setiap hari, tentukan BERAPA HARI LAGI
sampai muncul hari dengan suhu yang LEBIH TINGGI.
Jika tidak ada hari yang lebih panas setelahnya, cetak 0.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan suhu[i]

OUTPUT FORMAT:
- Satu baris berisi N bilangan dipisah spasi

CONSTRAINTS:
- 1 ≤ N ≤ 2*10^5
- 0 ≤ suhu[i] ≤ 100

SAMPLE INPUT 1:
6
73 74 75 71 69 72

SAMPLE OUTPUT 1:
1 1 0 2 1 0

SAMPLE INPUT 2:
4
30 30 30 30

SAMPLE OUTPUT 2:
0 0 0 0

NOTE: Simpan INDEKS di stack, bukan nilai — kamu butuh selisih posisi
      untuk menghitung jarak hari.
      Perhatikan sample 2: suhu yang SAMA tidak dihitung "lebih tinggi".
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

    vector<int> hasil(n, 0);

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] < arr[i])
        {
            hasil[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }

    for (int x : hasil)
    {
        cout << x << " ";
    }
}