/*
============================================================
📋 TUGAS 02: Cek Self-Loop dan Multi-Edge
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency list, directed graph, simple graph

PROBLEM:
Diberikan graph berarah dengan n node dan m edge.
Cetak:
1. Apakah ada self-loop (edge u→u)? Sebutkan semua node yang punya self-loop.
2. Apakah ada multi-edge (lebih dari 1 edge u→v)? Sebutkan semua pasangan.
3. Apakah ini "simple graph" (tidak ada self-loop maupun multi-edge)?

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (edge dari u ke v)

OUTPUT FORMAT:
- "Self-loop: node X" (satu per baris, sorted ascending) atau "Self-loop: TIDAK ADA"
- "Multi-edge: (U,V)" (satu per baris, sorted) atau "Multi-edge: TIDAK ADA"
- "Simple graph: YA" atau "Simple graph: TIDAK"

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 1 ≤ m ≤ 2×10^5

SAMPLE INPUT 1:
3 5
1 1
1 2
1 2
2 3
3 1

SAMPLE OUTPUT 1:
Self-loop: node 1
Multi-edge: (1,2)
Simple graph: TIDAK

SAMPLE INPUT 2:
4 3
1 2
2 3
3 4

SAMPLE OUTPUT 2:
Self-loop: TIDAK ADA
Multi-edge: TIDAK ADA
Simple graph: YA

NOTE: Gunakan set<pair<int,int>> untuk mendeteksi multi-edge.
      Self-loop jika u == v.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    set<int> selfLoopNodes;
    set<pair<int,int>> seen, multiEdges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            selfLoopNodes.insert(u);
        } else {
            auto e = make_pair(min(u,v), max(u,v));
            if (seen.count(e)) multiEdges.insert(e);
            else seen.insert(e);
        }
    }

    if (selfLoopNodes.empty())
        cout << "Self-loop: TIDAK ADA\n";
    else
        for (int x : selfLoopNodes) cout << "Self-loop: node " << x << '\n';

    if (multiEdges.empty())
        cout << "Multi-edge: TIDAK ADA\n";
    else
        for (auto [u,v] : multiEdges) cout << "Multi-edge: (" << u << "," << v << ")\n";

    bool simple = selfLoopNodes.empty() && multiEdges.empty();
    cout << "Simple graph: " << (simple ? "YA" : "TIDAK") << '\n';
    return 0;
}
