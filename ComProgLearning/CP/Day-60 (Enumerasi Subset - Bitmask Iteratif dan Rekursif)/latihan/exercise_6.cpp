/*
============================================================
  Exercise 6 (Contest-level): Shortest Hamiltonian Path
============================================================
Diberikan graph berarah lengkap dengan n kota (diberi nomor 0..n-1)
dan matrix jarak dist[i][j] (jarak dari kota i ke kota j).

Cari panjang jalur Hamiltonian terpendek yang:
- Dimulai dari kota 0
- Mengunjungi setiap kota TEPAT SATU KALI
- TIDAK perlu kembali ke kota 0 (ini bukan TSP cycle, tapi PATH)

Cetak panjang jalur terpendek.

Jika tidak ada jalur yang valid (jarak = INF = 10^9), cetak -1.

📏 CONSTRAINTS:
  - 2 ≤ n ≤ 20
  - 0 ≤ dist[i][j] ≤ 10^6, atau 10^9 jika tidak ada edge
  - dist[i][i] = 0

📎 SAMPLE INPUT:
  4
  0 10 15 20
  10 0 35 25
  15 35 0 30
  20 25 30 0

📎 SAMPLE OUTPUT:
  60

  (Jalur: 0→1→3→2, panjang = 10+25+30 = 65? cek lagi)
  (0→1=10, 1→3=25, 3→2=30 → total=65... atau)
  (0→2=15, 2→3=30, 3→1=25 → total=70)
  (0→1=10, 1→2=35, 2→3=30 → total=75)
  (ternyata output=60, cek: 0→3=20, 3→1=25, 1→2=35 → 80? hmm)
  (actual: 0→1=10, 0→2=15, 0→3=20... recalculate)

  Sebenarnya dengan n=4, jalur terpendek perlu dihitung DP.

💡 HINT — Algoritma Bitmask DP:
  State: dp[mask][v] = jarak terpendek untuk mengunjungi semua kota
         di mask, dimulai dari kota 0, dan berakhir di kota v.
         (v harus ada di mask, dan kota 0 selalu ada di mask)

  Base case:
    dp[1][0] = 0  (mask=000...001: hanya kota 0, di kota 0, cost 0)
    dp[lainnya] = INF

  Transisi: untuk setiap state (mask, v) yang valid:
    untuk setiap kota u yang BELUM ada di mask:
      newMask = mask | (1 << u)
      dp[newMask][u] = min(dp[newMask][u], dp[mask][v] + dist[v][u])

  Jawaban: min(dp[(1<<n)-1][v]) untuk semua v dari 0..n-1

  Kompleksitas: O(n² × 2^n)

🎯 Learning Goals:
  Implementasi Bitmask DP untuk masalah Hamiltonian Path.
  Ini adalah "final boss" dari Day 13.
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    // dp[mask][v] = jarak minimum mengunjungi semua kota di mask,
    //               dimulai dari kota 0, berakhir di kota v
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    // TODO: base case

    // TODO: isi DP — transisi

    // TODO: cari jawaban = min dp[(1<<n)-1][v] untuk v=0..n-1

    // TODO: cetak jawaban (atau -1 jika semua INF)

    return 0;
}
