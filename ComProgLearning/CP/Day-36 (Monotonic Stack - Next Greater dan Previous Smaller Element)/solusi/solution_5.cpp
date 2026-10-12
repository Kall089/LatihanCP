/*
============================================================
  Solution 5: Largest Rectangle in Histogram
============================================================
Kompleksitas: O(n) — monotonic increasing stack

Ide: saat memproses batang i yang lebih rendah dari top,
pop top dan hitung luas rectangle dengan tinggi h[top].
Lebar = i - (new_top) - 1
Tambahkan sentinel h=0 di kanan (index n) agar stack dikosongkan.
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
    stack<int> st;

    for (int i = 0; i <= n; i++) {
        ll cur = (i == n) ? 0 : h[i];
        while (!st.empty() && h[st.top()] > cur) {
            ll height = h[st.top()]; st.pop();
            ll width = st.empty() ? i : i - st.top() - 1;
            ans = max(ans, height * width);
        }
        st.push(i);
    }

    cout << ans << "\n";
    return 0;
}
