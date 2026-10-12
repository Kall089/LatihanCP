/*
============================================================
📋 TUGAS 05: Reverse / Transpose Graph
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency list, directed graph, transpose

PROBLEM:
Diberikan graph berarah dengan n node dan m edge.
Buat dan cetak adjacency list dari graph transpose-nya
(balik arah SEMUA edge: u→v menjadi v→u).

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (edge dari u ke v)

OUTPUT FORMAT:
- n baris: "X: a b c ..." (tetangga di transpose, sorted ascending)
  Jika tidak ada tetangga, cetak "X: (kosong)"

CONSTRAINTS:
- 1 ≤ n, m ≤ 10^5

SAMPLE INPUT 1:
4 4
1 2
2 3
3 4
4 1

SAMPLE OUTPUT 1:
1: 4
2: 1
3: 2
4: 3

SAMPLE INPUT 2:
3 2
1 2
1 3

SAMPLE OUTPUT 2:
1: (kosong)
2: 1
3: 1

NOTE: Transpose berguna untuk algoritma Kosaraju (Strongly Connected Components).
      Cara: untuk setiap edge (u,v), tambahkan ke adj_T[v].push_back(u).
      Sort tiap adj_T[i] sebelum cetak.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adjT(n + 1);  // transpose adjacency list
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adjT[v].push_back(u);  // reverse edge: u→v becomes v→u
    }

    for (int i = 1; i <= n; i++) {
        sort(adjT[i].begin(), adjT[i].end());
        cout << i << ": ";
        if (adjT[i].empty()) cout << "(kosong)";
        else for (int j = 0; j < (int)adjT[i].size(); j++) {
            if (j) cout << ' ';
            cout << adjT[i][j];
        }
        cout << '\n';
    }
    return 0;
}
