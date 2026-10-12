/*
============================================================
✅ Solution 5: Difference Array 2D (Range Update Offline)
============================================================
Approach: 2D Difference Array + Prefix Sum 2D Reconstruction
Complexity: Time O(Q + N × M) | Space O(N × M)
Key Insight:
Untuk melakukan update +val pada area (r1, c1) hingga (r2, c2) secara O(1):
  diff[r1][c1] += val;
  diff[r1][c2 + 1] -= val;
  diff[r2 + 1][c1] -= val;
  diff[r2 + 1][c2 + 1] += val;

Setelah semua Q update selesai, jalankan Prefix Sum 2D pada matriks `diff`:
  diff[i][j] = diff[i][j] + diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1]
Matriks `diff` kini berisi nilai akhir dari seluruh update.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // Gunakan n+2 dan m+2 untuk mengantisipasi c2+1 dan r2+1
    vector<vector<long long>> diff(n + 2, vector<long long>(m + 2, 0));

    while (q--) {
        int r1, c1, r2, c2;
        long long val;
        cin >> r1 >> c1 >> r2 >> c2 >> val;

        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // Rekonstruksi dengan Prefix Sum 2D secara in-place
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }

    // Cetak hasil
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << diff[i][j] << (j == m ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
