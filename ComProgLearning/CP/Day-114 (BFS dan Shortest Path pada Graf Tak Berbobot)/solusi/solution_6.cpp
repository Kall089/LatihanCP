/*
============================================================
  Solution 6: 0-1 BFS dengan Deque
============================================================
Kompleksitas: O(R × C)

Cara kerja:
- Gunakan deque<pair<int,int>> sebagai pengganti queue
- Edge weight = 0 (nilai sama): push_front → tidak tambah jarak
- Edge weight = 1 (nilai beda): push_back → tambah jarak 1
- Cek dist[r][c] + cost < dist[nr][nc] (bukan == -1)
  karena node bisa diproses ulang jika ditemukan jarak lebih kecil
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

    const int INF = 1e9;
    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, INF));
    deque<pair<int, int>> dq;

    dist[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty()) {
        auto [r, c] = dq.front(); dq.pop_front();

        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

            int cost = (grid[nr][nc] != grid[r][c]) ? 1 : 0;

            if (dist[r][c] + cost < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + cost;
                if (cost == 0) dq.push_front({nr, nc});
                else           dq.push_back({nr, nc});
            }
        }
    }

    cout << dist[R - 1][C - 1] << "\n";

    return 0;
}
