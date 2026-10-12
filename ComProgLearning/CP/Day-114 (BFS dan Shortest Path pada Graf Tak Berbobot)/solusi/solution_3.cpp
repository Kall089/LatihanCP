/*
============================================================
  Solution 3: BFS pada Grid
============================================================
Kompleksitas: O(R × C)

Cara kerja:
- Cari posisi 'S' dan 'T' di grid
- BFS dari 'S', bergerak 4 arah
- Abaikan '#' (tembok) dan sel yang sudah dikunjungi
- Output dist[er][ec], atau -1 jika tidak terjangkau
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

    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 'S') { sr = r; sc = c; }
            if (grid[r][c] == 'T') { er = r; ec = c; }
        }

    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << dist[er][ec] << "\n";

    return 0;
}
