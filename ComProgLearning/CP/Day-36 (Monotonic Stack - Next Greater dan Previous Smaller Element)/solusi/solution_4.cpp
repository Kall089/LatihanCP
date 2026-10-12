/*
============================================================
  Solution 4: Stock Span Problem
============================================================
Kompleksitas: O(n) — monotonic decreasing stack (store index)

span[i] = i - (index Previous Greater Element) dari harga[i]
Jika tidak ada PGE → span[i] = i + 1
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
    stack<int> st; // menyimpan index

    for (int i = 0; i < n; i++) {
        while (!st.empty() && price[st.top()] <= price[i])
            st.pop();
        span[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }

    for (int i = 0; i < n; i++)
        cout << span[i] << " \n"[i == n-1];
    return 0;
}
