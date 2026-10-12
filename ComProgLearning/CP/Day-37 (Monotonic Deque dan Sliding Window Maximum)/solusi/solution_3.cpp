/*
============================================================
  Solution 3: Sliding Window Maximum
============================================================
Kompleksitas: O(n) — setiap elemen masuk dan keluar deque tepat sekali
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dq; // menyimpan INDEX, nilai menurun
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() <= i-k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k-1) cout << a[dq.front()] << " \n"[i==n-1];
    }
    return 0;
}
