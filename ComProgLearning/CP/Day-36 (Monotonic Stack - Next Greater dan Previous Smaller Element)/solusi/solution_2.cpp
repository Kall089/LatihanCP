/*
============================================================
  Solution 2: Next Greater Element
============================================================
Kompleksitas: O(n) — setiap elemen push/pop tepat satu kali

Cara kerja: monotonic decreasing stack (store index)
  - Saat A[i] > A[st.top()], maka NGE dari st.top() adalah A[i]
  - Pop dan set nge[popped] = A[i]
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> nge(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            nge[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }

    for (int i = 0; i < n; i++)
        cout << nge[i] << " \n"[i == n-1];
    return 0;
}
