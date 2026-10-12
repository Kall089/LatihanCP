/*
============================================================
  Exercise 4: Stock Span Problem
============================================================
Diberikan harga saham selama n hari berturut-turut. Stock span pada hari i
didefinisikan sebagai jumlah hari berturut-turut (termasuk hari i) di mana
harga saham ≤ harga pada hari i.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 1 ≤ harga[i] ≤ 10^9

📎 SAMPLE INPUT:
  7
  100 80 60 70 60 75 85

📎 SAMPLE OUTPUT:
  1 1 1 2 1 4 6

📎 SAMPLE INPUT 2:
  5
  10 4 5 90 120

📎 SAMPLE OUTPUT 2:
  1 1 2 4 5

💡 HINT:
  - Ini setara dengan Previous Greater Element (PGE)
  - span[i] = i - index(PGE[i])
  - Gunakan monotonic stack yang menyimpan index
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> price(n);
    for (int i = 0; i < n; i++) cin >> price[i];

    vector<int> span(n);
    stack<int> st; // simpan index

    for (int i = 0; i < n; i++) {
        // TODO: hitung span[i]
        // Hint: pop elemen dengan price <= price[i]
        // span[i] = i - st.top() (atau i+1 jika kosong)
    }

    for (int i = 0; i < n; i++)
        cout << span[i] << " \n"[i == n-1];
    return 0;
}
