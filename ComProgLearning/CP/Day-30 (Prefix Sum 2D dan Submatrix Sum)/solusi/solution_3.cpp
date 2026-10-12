/*
============================================================
✅ Solution 3: Forest Queries (Jumlah Pohon di Area Grid)
============================================================
Approach: Prefix Sum 2D pada Character Grid
Complexity: Time O(N^2 + Q) | Space O(N^2)
Key Insight:
Ubah karakter '*' menjadi 1 dan '.' menjadi 0.
Bangun tabel prefix sum 2D berukuran (N+1) × (N+1).
Jawab setiap query dalam O(1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q))
        return 0;

    vector<vector<int>> psum(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++)
        {
            int val = (s[j - 1] == '*' ? 1 : 0);
            psum[i][j] = val + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }

    while (q--)
    {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        int ans = psum[y2][x2] - psum[y1 - 1][x2] - psum[y2][x1 - 1] + psum[y1 - 1][x1 - 1];
        cout << ans << "\n";
    }

    return 0;
}
