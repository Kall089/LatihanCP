/*
============================================================
📋 TUGAS 07: Count Connected Components (Grid)
============================================================
Source: Original
Difficulty: Medium
Topics: implicit graph, BFS/DFS, connected components, grid

PROBLEM:
Diberikan grid n×m berisi '.' (tanah) dan '#' (tembok).
Hitung jumlah "pulau": kelompok sel '.' yang terhubung secara
4-arah (atas, bawah, kiri, kanan). Ini adalah preview BFS/DFS.

INPUT FORMAT:
- Baris 1: dua integer n dan m
- n baris berikutnya: string sepanjang m berisi '.' dan '#'

OUTPUT FORMAT:
- Satu baris: "Jumlah pulau: K"

CONSTRAINTS:
- 1 ≤ n, m ≤ 1000

SAMPLE INPUT 1:
4 5
.....
.###.
.###.
.....

SAMPLE OUTPUT 1:
Jumlah pulau: 1

SAMPLE INPUT 2:
3 3
.#.
###
.#.

SAMPLE OUTPUT 2:
Jumlah pulau: 4

NOTE: Untuk sample 1, semua '.' terhubung melalui tepi atas dan bawah → 1 pulau.
      Untuk sample 2, keempat sudut '.' masing-masing terisolasi → 4 pulau.
      Gunakan BFS/DFS dari setiap '.' yang belum dikunjungi.
      Arah gerak: dx[]={0,0,1,-1}, dy[]={1,-1,0,0}.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int islands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !vis[i][j]) {
                islands++;
                // BFS from (i, j)
                queue<pair<int,int>> q;
                q.push({i, j});
                vis[i][j] = true;
                while (!q.empty()) {
                    auto [r, c] = q.front(); q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dx[d], nc = c + dy[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < m
                            && !vis[nr][nc] && grid[nr][nc] == '.') {
                            vis[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }
    }

    cout << "Jumlah pulau: " << islands << '\n';
    return 0;
}
