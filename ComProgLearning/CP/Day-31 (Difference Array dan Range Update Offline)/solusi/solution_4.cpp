/*
============================================================
✅ Solution 4: Difference Array 2D — Cat Dinding
============================================================
Approach: Difference Array 2D + rekonstruksi prefix sum 2D
Complexity: Time O(N*M + Q) | Space O(N*M)
Key Insight:
Menambah v pada submatriks sama dengan menandai empat sudut:
  (r1, c1)         : +v   mulai berlaku
  (r1, c2+1)       : -v   matikan kebocoran ke kanan
  (r2+1, c1)       : -v   matikan kebocoran ke bawah
  (r2+1, c2+1)     : +v   pojok ini terlanjur dimatikan 2x, kembalikan 1x
Prefix sum 2D kemudian "menyalakan" nilai v tepat di dalam persegi panjang.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // (n+2) x (m+2) supaya indeks r2+1 dan c2+1 selalu aman
    vector<vector<ll>> d(n + 2, vector<ll>(m + 2, 0));

    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2;
        ll v;
        cin >> r1 >> c1 >> r2 >> c2 >> v;
        d[r1][c1]         += v;
        d[r1][c2 + 1]     -= v;
        d[r2 + 1][c1]     -= v;
        d[r2 + 1][c2 + 1] += v;
    }

    // Rekonstruksi: prefix sum 2D in-place
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cout << d[i][j] << " \n"[j == m];

    return 0;
}
