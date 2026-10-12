/*
============================================================
✅ Solution 2: Maximum Submatrix Sum ukuran K × L
============================================================
Approach: Prefix Sum 2D + 2D Sliding Window / Fixed Size Iteration
Complexity: Time O(N × M) | Space O(N × M)
Key Insight:
Bangun tabel psum 2D. Lalu iterasi seluruh kemungkinan titik kanan-bawah (i, j)
dari submatriks K × L, di mana K ≤ i ≤ N dan L ≤ j ≤ M.
Titik kiri-atas otomatis adalah (i - K + 1, j - L + 1).
Hitung sum dalam O(1) dan ambil nilai terbesarnya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k, l;
    if (!(cin >> n >> m >> k >> l))
        return 0;

    vector<vector<long long>> psum(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            long long val;
            cin >> val;
            psum[i][j] = val + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }

    long long max_sum = -1e18; // Inisialisasi minus infinity

    for (int i = k; i <= n; i++)
    {
        for (int j = l; j <= m; j++)
        {
            int r1 = i - k + 1;
            int c1 = j - l + 1;
            int r2 = i;
            int c2 = j;

            long long current_sum = psum[r2][c2] - psum[r1 - 1][c2] - psum[r2][c1 - 1] + psum[r1 - 1][c1 - 1];
            max_sum = max(max_sum, current_sum);
        }
    }

    cout << max_sum << "\n";

    return 0;
}
