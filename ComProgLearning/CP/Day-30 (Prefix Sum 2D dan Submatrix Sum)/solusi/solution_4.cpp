/*
============================================================
✅ Solution 4: Maximum Submatrix Sum (Ukuran Bebas)
============================================================
Approach: 2D Kadane / Prefix Sum 2D Row Compression + 1D Kadane
Complexity: Time O(N^2 × M) | Space O(N × M)
Key Insight:
Dengan menetapkan baris atas r1 dan baris bawah r2, kita dapat mengompresi
elemen pada setiap kolom j dari baris r1 ke r2 menjadi satu nilai:
col[j] = psum[r2][j] - psum[r1-1][j] - psum[r2][j-1] + psum[r1-1][j-1] (atau langsung sum 1D kolom).
Kemudian, jalankan Algoritma Kadane 1D pada array `col` untuk menemukan
subarray maksimum dalam O(M). Total waktu O(N^2 × M).
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

    long long max_sum = -1e18;

    // Fix baris r1 dan r2
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            // Kadane 1D pada kompresi kolom
            long long current_running_sum = 0;
            for (int c = 1; c <= m; c++) {
                // Sum kolom c dari baris r1 ke r2
                long long col_val = psum[r2][c] - psum[r1 - 1][c] - (psum[r2][c - 1] - psum[r1 - 1][c - 1]);
                
                current_running_sum += col_val;
                max_sum = max(max_sum, current_running_sum);
                
                if (current_running_sum < 0) {
                    current_running_sum = 0;
                }
            }
        }
    }

    cout << max_sum << "\n";

    return 0;
}
