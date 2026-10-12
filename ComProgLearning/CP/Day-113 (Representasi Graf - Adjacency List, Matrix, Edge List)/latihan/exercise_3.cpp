/*
============================================================
  Exercise 3: Degree Sequence & Properti Graph Dasar
============================================================
Diberikan graph tidak berarah. Hitung dan tampilkan:
1. Degree sequence (urutan degree semua node, descending)
2. Total edge (verifikasi dengan handshaking lemma)
3. Node terisolasi (degree = 0)
4. Apakah graph memenuhi kondisi Euler Circuit
   (semua degree genap dan graph connected)
5. Apakah graph memenuhi kondisi Euler Path
   (tepat 2 node ber-degree ganjil dan graph connected)

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 0 ≤ m ≤ 2×10^5

📎 SAMPLE INPUT 1:
  4 4
  1 2
  2 3
  3 4
  4 1

📎 SAMPLE OUTPUT 1:
  Degree sequence: [2, 2, 2, 2]
  Total edge: 4
  Node terisolasi: (tidak ada)
  Euler Circuit: MUNGKIN ADA
  Euler Path: TIDAK

📎 SAMPLE INPUT 2:
  4 3
  1 2
  2 3
  3 4

📎 SAMPLE OUTPUT 2:
  Degree sequence: [2, 1, 1, 2] → [2, 2, 1, 1]
  Total edge: 3
  Node terisolasi: (tidak ada)
  Euler Circuit: TIDAK
  Euler Path: MUNGKIN ADA

💡 HINT Euler Circuit: semua degree genap
💡 HINT Euler Path: tepat 2 node degree ganjil
   (Catatan: untuk kondisi ini perlu juga graph terhubung — abaikan
    pengecekan connected untuk exercise ini, fokus ke degree saja)

🎯 Learning Goals:
  Analisis properti dasar graph dari adjacency list.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // TODO: deklarasi dan isi adjacency list
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        // TODO
    }

    // TODO: hitung degree tiap node
    vector<int> deg(n + 1, 0);
    // TODO

    // TODO: buat degree sequence (sort descending)

    // TODO: cetak degree sequence

    // TODO: cetak total edge (sum degree / 2)

    // TODO: cari node terisolasi

    // TODO: cek Euler Circuit (semua degree genap)

    // TODO: cek Euler Path (tepat 2 node degree ganjil)

    return 0;
}
