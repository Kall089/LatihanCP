/*
============================================================
  Exercise 4: Multi-source BFS
============================================================
Diberikan grid R baris dan C kolom:
  '1' = daratan
  '0' = lautan

Untuk setiap sel lautan, hitung jarak ke daratan terdekat
(dalam langkah 4-arah). Jika tidak ada daratan atau tidak ada
lautan, cetak -1.

Cetak satu angka: jarak maksimum dari semua sel lautan ke
daratan terdekat (yaitu, jarak lautan yang "paling jauh" dari
daratan manapun).

📏 CONSTRAINTS:
  - 1 ≤ R, C ≤ 100
  - Grid hanya berisi '0' dan '1'

📎 SAMPLE INPUT:
  4 4
  0010
  0000
  0100
  0000

📎 SAMPLE OUTPUT:
  3

📎 SAMPLE INPUT 2:
  3 3
  111
  111
  111

📎 SAMPLE OUTPUT 2:
  -1

(karena tidak ada lautan sama sekali)

💡 HINT:
  - Multi-source BFS: masukkan SEMUA daratan ke queue awal dengan dist=0
  - BFS menyebar dari semua daratan sekaligus
  - Jawaban = max dari dist[r][c] untuk semua sel lautan
  - Jika tidak ada lautan atau tidak ada daratan → cetak -1

🎯 Learning Goals:
  Multi-source BFS lebih efisien daripada menjalankan BFS
  terpisah dari setiap source. Kompleksitas tetap O(R×C).
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

    // TODO: cek apakah ada daratan dan ada lautan
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

    // TODO: inisialisasi dist dan queue
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;

    // TODO: masukkan SEMUA daratan ke queue dengan dist = 0

    // TODO: jalankan BFS (multi-source)

    // TODO: cari nilai maksimum dari dist[r][c] untuk semua lautan
    int ans = 0;
    // TODO: loop semua sel, update ans

    cout << ans << "\n";
    return 0;
}
