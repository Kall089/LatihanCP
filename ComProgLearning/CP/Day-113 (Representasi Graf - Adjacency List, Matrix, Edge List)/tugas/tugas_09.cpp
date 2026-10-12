/*
============================================================
📋 TUGAS 09: Bangun Graph Berbobot dengan Batas Biaya
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency list, weighted graph, edge filtering

PROBLEM:
Diberikan n kota, m rencana jalan dengan biaya, dan batas biaya L.
Bangun adjacency list hanya dari jalan dengan biaya ≤ L.
Cetak adjacency list (tetangga diurutkan berdasarkan nomor node).
Cetak juga kota-kota yang "terisolasi" (tidak punya jalan sama sekali
setelah filter). Jika tidak ada, cetak "Tidak ada kota terisolasi."

INPUT FORMAT:
- Baris 1: tiga integer n, m, dan L
- m baris berikutnya: tiga integer u v cost (jalan u-v berbiaya cost)

OUTPUT FORMAT:
- n baris adj list: "X: u(cu) v(cv) ..." atau "X: (kosong)"
- Satu baris info kota terisolasi

CONSTRAINTS:
- 1 ≤ n ≤ 10^3
- 1 ≤ m ≤ 10^4
- 1 ≤ L, cost ≤ 10^6

SAMPLE INPUT 1:
5 5 6
1 2 5
1 3 3
2 4 7
1 4 4
3 5 6

SAMPLE OUTPUT 1:
1: 2(5) 3(3) 4(4)
2: 1(5)
3: 1(3) 5(6)
4: 1(4)
5: 3(6)
Tidak ada kota terisolasi.

SAMPLE INPUT 2:
4 4 3
1 2 5
2 3 2
3 4 6
1 4 7

SAMPLE OUTPUT 2:
1: (kosong)
2: 3(2)
3: 2(2)
4: (kosong)
Kota terisolasi: 1 4

NOTE: Hanya tambahkan edge (u,v,cost) jika cost ≤ L.
      Kota terisolasi = kota dengan degree 0 setelah filtering.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, L;
    cin >> n >> m >> L;

    // adj[u] = vector of (v, cost), sorted by v
    vector<vector<pair<int,int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        if (cost <= L) {
            adj[u].push_back({v, cost});
            adj[v].push_back({u, cost});
        }
    }

    // Sort each adjacency list by node number
    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end());

    vector<int> isolated;
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        if (adj[i].empty()) {
            cout << "(kosong)";
            isolated.push_back(i);
        } else {
            for (int j = 0; j < (int)adj[i].size(); j++) {
                if (j) cout << ' ';
                cout << adj[i][j].first << '(' << adj[i][j].second << ')';
            }
        }
        cout << '\n';
    }

    if (isolated.empty()) {
        cout << "Tidak ada kota terisolasi.\n";
    } else {
        cout << "Kota terisolasi:";
        for (int x : isolated) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}
