/*
============================================================
  Exercise 3: Previous Smaller Element
============================================================
Diberikan array A dengan n elemen. Untuk setiap elemen A[i],
temukan Previous Smaller Element (PSE) — elemen pertama di sebelah kiri
yang lebih kecil dari A[i]. Jika tidak ada, output -1.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 1 ≤ A[i] ≤ 10^9

📎 SAMPLE INPUT:
  6
  3 1 2 5 2 4

📎 SAMPLE OUTPUT:
  -1 -1 1 2 1 2

💡 HINT:
  - Monotonic stack dari kiri ke kanan
  - Sebelum push A[i], pop semua elemen ≥ A[i]
  - PSE[i] = top stack setelah pop (atau -1 jika kosong)
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
    while (!st.empty() && arr[i] <= arr[st.top()])
    {
      hasil[st.top()] = (arr[i]);
      st.pop();
    }
    st.push(arr[i]);
  }

  for (int x : hasil)
  {
    cout << x << " ";
  }
}