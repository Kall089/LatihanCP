/*
============================================================
  Exercise 2: BFS Shortest Path Unweighted
============================================================
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge. Diberikan juga node asal S dan node tujuan T.
Temukan panjang path terpendek dari S ke T (dalam jumlah edge),
dan cetak salah satu path terpendek tersebut.

Jika tidak ada path dari S ke T, cetak "TIDAK ADA PATH".

📏 CONSTRAINTS:
  - 2 ≤ n ≤ 10^5
  - 1 ≤ m ≤ 2×10^5
  - 1 ≤ S, T ≤ n, S ≠ T
  - Node 1-indexed

📎 SAMPLE INPUT:
  5 5
  1 2
  1 3
  2 4
  3 4
  4 5
  1 5

📎 SAMPLE OUTPUT:
  Panjang path terpendek: 3
  Path: 1 -> 2 -> 4 -> 5

📎 SAMPLE INPUT 2:
  4 2
  1 2
  3 4
  1 4

📎 SAMPLE OUTPUT 2:
  TIDAK ADA PATH

💡 HINT:
  - Simpan prev[v] = parent v saat BFS
  - Rekonstruksi: mulai dari T, ikuti prev[] sampai S
  - Balik hasilnya (karena trace dari T ke S)

🎯 Learning Goals:
  BFS otomatis menemukan shortest path pada unweighted graph.
  Simpan prev[] untuk rekonstruksi path.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // TODO: deklarasi adjacency list
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // TODO: tambah edge undirected
    }

    int S, T;
    cin >> S >> T;

    // TODO: BFS dari S, simpan dist[] dan prev[]
    vector<int> dist(n + 1, -1);
    vector<int> prev(n + 1, -1);
    queue<int> q;

    // TODO: inisialisasi BFS dari S

    // TODO: loop BFS (simpan prev[v] = u saat push v)

    // TODO: cek apakah T terjangkau
    if (dist[T] == -1) {
        cout << "TIDAK ADA PATH\n";
    } else {
        cout << "Panjang path terpendek: " << dist[T] << "\n";
        // TODO: rekonstruksi path dari T ke S lewat prev[]
        // lalu balik dan cetak
        cout << "Path: ";
        // TODO: cetak path dalam format "a -> b -> c -> ..."
    }

    return 0;
}
