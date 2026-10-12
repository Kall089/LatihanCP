/*
============================================================
  Exercise 3: BFS pada Grid — Hitung Langkah ke Tujuan
============================================================
Diberikan grid R baris dan C kolom. Setiap sel berisi:
  '.' = bisa dilalui
  '#' = tembok (tidak bisa dilewati)
  'S' = posisi awal
  'T' = posisi tujuan

Hitung jumlah langkah minimum dari S ke T dengan bergerak
4-arah (atas, bawah, kiri, kanan).
Jika tidak ada jalur, cetak -1.

📏 CONSTRAINTS:
  - 1 ≤ R, C ≤ 1000
  - Grid dijamin mengandung tepat 1 'S' dan 1 'T'
  - Pergerakan: 4 arah (atas, bawah, kiri, kanan)

📎 SAMPLE INPUT:
  5 7
  #######
  #S....#
  ###.###
  #....T#
  #######

📎 SAMPLE OUTPUT:
  8

📎 SAMPLE INPUT 2:
  3 3
  S.#
  ###
  #.T

📎 SAMPLE OUTPUT 2:
  -1

💡 HINT:
  - Cari posisi 'S' dan 'T' dengan loop 2D
  - Gunakan dist[r][c] diinisialisasi -1
  - Cek batas array sebelum pindah ke sel baru
  - Cek '#' sebelum masuk sel baru

🎯 Learning Goals:
  BFS pada grid adalah aplikasi BFS paling umum di CP.
  Pola dx/dy untuk 4 arah wajib dihafal.
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

    // TODO: cari posisi S dan T
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            // TODO: jika grid[r][c] == 'S', simpan sr, sc
            // TODO: jika grid[r][c] == 'T', simpan er, ec
        }
    }

    // 4-arah: atas, bawah, kiri, kanan
    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    // TODO: BFS dari (sr, sc)
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;

    // TODO: inisialisasi BFS

    // TODO: loop BFS pada grid

    // TODO: cetak dist[er][ec]

    return 0;
}
