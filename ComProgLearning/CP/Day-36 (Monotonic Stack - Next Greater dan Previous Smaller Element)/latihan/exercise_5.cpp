/*
============================================================
  Exercise 5: Largest Rectangle in Histogram
============================================================
Diberikan histogram dengan n batang, lebar masing-masing 1 unit,
tinggi batang ke-i adalah h[i]. Temukan luas persegi panjang terbesar
yang dapat dibentuk di dalam histogram tersebut.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 0 ≤ h[i] ≤ 10^9

📎 SAMPLE INPUT:
  6
  2 1 5 6 2 3

📎 SAMPLE OUTPUT:
  10

📎 SAMPLE INPUT 2:
  3
  3 3 3

📎 SAMPLE OUTPUT 2:
  9

💡 HINT:
  - Untuk tiap batang i: luas = h[i] × (right[i] - left[i] - 1)
  - right[i] = index first bar dengan h < h[i] di sebelah kanan
  - left[i]  = index first bar dengan h < h[i] di sebelah kiri
  - Gunakan monotonic stack untuk menghitung left[] dan right[]
  - Atau: satu pass dengan stack, proses saat pop
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    ll ans = 0;
    stack<int> st; // monotonic increasing stack of indices

    for (int i = 0; i <= n; i++) {
        ll cur = (i == n) ? 0 : h[i];
        while (!st.empty() && h[st.top()] > cur) {
            // TODO: hitung luas persegi panjang dengan h[st.top()]
        }
        st.push(i);
    }

    cout << ans << "\n";
    return 0;
}
