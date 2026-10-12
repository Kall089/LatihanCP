/*
============================================================
  Solution 4: Multi-source BFS
============================================================
Kompleksitas: O(R × C)

Cara kerja:
- Masukkan SEMUA sel daratan ('1') ke queue awal dengan dist = 0
- BFS menyebar dari semua daratan sekaligus
- Setiap sel lautan ('0') mendapat dist = jarak ke daratan terdekat
- Jawaban = max(dist) dari semua sel lautan
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C; cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    bool hasDaratan = false, hasLautan = false;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == '1') hasDaratan = true;
            if (grid[r][c] == '0') hasLautan = true;
        }

    if (!hasDaratan || !hasLautan) {
        cout << -1 << "\n";
        return 0;
    }

    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int, int>> q;

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == '1') {
                dist[r][c] = 0;
                q.push({r, c});
            }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    int ans = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == '0')
                ans = max(ans, dist[r][c]);

    cout << ans << "\n";

    return 0;
}
