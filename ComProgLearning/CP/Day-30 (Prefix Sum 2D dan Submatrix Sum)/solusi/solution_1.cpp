/*
============================================================
✅ Solution 1: Submatrix Sum Query Dasar
============================================================
Approach: Prefix Sum 2D (Inclusion-Exclusion)
Complexity: Time O(N × M + Q) | Space O(N × M)
Key Insight: 
Dengan menyimpan jumlah kumulatif dari (1,1) ke (i,j) pada psum[i][j],
setiap query submatriks (r1,c1) hingga (r2,c2) dapat dijawab dalam O(1)
menggunakan rumus:
sum = psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1]
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<long long>> a(n + 1, vector<long long>(m + 1, 0));
    vector<vector<long long>> psum(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            psum[i][j] = a[i][j] + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        long long ans = psum[r2][c2] - psum[r1 - 1][c2] - psum[r2][c1 - 1] + psum[r1 - 1][c1 - 1];
        cout << ans << "\n";
    }

    return 0;
}
