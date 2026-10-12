/*
============================================================
  Exercise 6: 0-1 BFS dengan Deque (Challenge)
============================================================
Diberikan grid R×C. Setiap sel berisi '0' atau '1'.
Bergerak dari sel (0,0) ke sel (R-1,C-1) dengan biaya:
  - Bergerak ke sel yang nilainya SAMA dengan sel saat ini: biaya 0
  - Bergerak ke sel yang nilainya BERBEDA: biaya 1

Temukan biaya minimum untuk mencapai (R-1,C-1) dari (0,0).
Pergerakan 4-arah.

Ini adalah soal 0-1 BFS: edge weight hanya 0 atau 1.
Gunakan DEQUE, bukan queue biasa.

📏 CONSTRAINTS:
  - 1 ≤ R, C ≤ 100
  - Grid hanya berisi '0' dan '1'

📎 SAMPLE INPUT:
  3 3
  010
  011
  110

📎 SAMPLE OUTPUT:
  1

(Satu path minimum: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)
  Biaya: perubahan di 0→1 = 1, total = 1)

📎 SAMPLE INPUT 2:
  2 2
  00
  00

📎 SAMPLE OUTPUT 2:
  0

(Semua sama, tidak ada perubahan)

💡 HINT:
  - 0-1 BFS: gunakan deque<pair<int,int>>
  - Jika pindah ke sel dengan nilai SAMA: push_front (cost 0)
  - Jika pindah ke sel dengan nilai BERBEDA: push_back (cost 1)
  - dist[r][c] = biaya minimum dari (0,0) ke (r,c)
  - Inisialisasi dist dengan INF, dist[0][0] = 0

🎯 Learning Goals:
  0-1 BFS adalah alternatif Dijkstra yang lebih cepat (O(RC))
  ketika edge weight hanya 0 atau 1. Teknik deque sangat powerful.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;

    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    const int INF = 1e9;
    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    // TODO: inisialisasi dist dengan INF
    vector<vector<int>> dist(R, vector<int>(C, INF));

    // TODO: gunakan deque<pair<int,int>>
    deque<pair<int,int>> dq;

    // TODO: inisialisasi: dist[0][0] = 0, push (0,0) ke depan deque

    // TODO: loop 0-1 BFS
    // while (!dq.empty()) {
    //     auto [r, c] = dq.front(); dq.pop_front();
    //     for setiap tetangga (nr, nc):
    //         cost = (grid[nr][nc] != grid[r][c]) ? 1 : 0;
    //         if (dist[r][c] + cost < dist[nr][nc]) {
    //             dist[nr][nc] = dist[r][c] + cost;
    //             if (cost == 0) dq.push_front({nr, nc});
    //             else           dq.push_back({nr, nc});
    //         }
    // }

    cout << dist[R-1][C-1] << "\n";
    return 0;
}
