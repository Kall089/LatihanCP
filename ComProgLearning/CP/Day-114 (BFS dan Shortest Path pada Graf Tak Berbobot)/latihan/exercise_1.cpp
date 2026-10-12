/*
============================================================
  Exercise 1: BFS Dasar — Kunjungi Semua Node dari Source
============================================================
Diberikan graph tidak berarah dan tidak berbobot dengan n node
dan m edge. Dari node source s, lakukan BFS dan cetak:
1. Urutan node yang dikunjungi (urutan BFS)
2. Jarak (distance) setiap node dari s
3. Node yang TIDAK TERJANGKAU dari s

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 0 ≤ m ≤ 2×10^5
  - 1 ≤ s ≤ n
  - Node 1-indexed

📎 SAMPLE INPUT:
  6 6 1
  1 2
  1 3
  2 4
  2 5
  3 6
  4 5

📎 SAMPLE OUTPUT:
  === Urutan BFS ===
  1 2 3 4 5 6
  === Jarak dari node 1 ===
  dist(1) = 0
  dist(2) = 1
  dist(3) = 1
  dist(4) = 2
  dist(5) = 2
  dist(6) = 2
  === Node Tidak Terjangkau ===
  Semua node terjangkau

💡 HINT:
  - Gunakan queue<int> untuk BFS
  - dist[v] = -1 berarti belum dikunjungi
  - Saat push v ke queue, langsung set dist[v] = dist[u] + 1

🎯 Learning Goals:
  Memahami mekanisme BFS dengan queue dan visited array.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m, s;
  cin >> n >> m >> s;

  for (int i = 0; i < n; i++) {
    
  }
}