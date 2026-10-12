/*
============================================================
  Solution 6: BFS Level Order Traversal
============================================================
Kompleksitas: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> vals(n);
    for (int i = 0; i < n; i++) cin >> vals[i];

    if (n == 0 || vals[0] == -1) return 0;

    queue<int> q;
    q.push(0);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        while (sz--) {
            int idx = q.front(); q.pop();
            cout << vals[idx];
            if (sz) cout << ' ';
            int l = 2*idx+1, r = 2*idx+2;
            if (l < n && vals[l] != -1) q.push(l);
            if (r < n && vals[r] != -1) q.push(r);
        }
        cout << "\n"; level++;
    }
    return 0;
}
