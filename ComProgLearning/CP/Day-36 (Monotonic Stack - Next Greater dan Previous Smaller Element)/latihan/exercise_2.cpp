/*
============================================================
  Exercise 2: Next Greater Element
============================================================
Diberikan array A dengan n elemen. Untuk setiap elemen A[i],
temukan Next Greater Element (NGE) — elemen pertama di sebelah kanan
yang lebih besar dari A[i]. Jika tidak ada, output -1.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 1 ≤ A[i] ≤ 10^9

📎 SAMPLE INPUT:
  6
  4 5 2 25 7 8

📎 SAMPLE OUTPUT:
  5 25 25 -1 8 -1

💡 HINT:
  - Gunakan monotonic stack (decreasing)
  - Iterasi dari kiri ke kanan
  - Saat elemen baru x lebih besar dari top stack → top itu punya NGE = x
  - Pop semua elemen yang lebih kecil dari x
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
    while (!st.empty() && arr[st.top()] < arr[i])
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