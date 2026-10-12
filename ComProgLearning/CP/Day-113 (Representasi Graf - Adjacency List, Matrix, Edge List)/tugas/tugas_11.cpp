/*
============================================================
📋 TUGAS 11: Social Network Analysis
============================================================
Source: Original
Difficulty: Medium
Topics: adjacency list, degree, graph analysis

PROBLEM:
Diberikan jaringan pertemanan (undirected) dengan n orang dan m relasi.
Jawab tiga pertanyaan:
1. Siapa yang punya teman paling banyak? (semua node dengan max degree)
2. Siapa yang tidak punya teman sama sekali? (degree 0)
3. Siapa yang punya tepat satu teman? (degree 1)

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (pertemanan u-v)

OUTPUT FORMAT:
- "Teman terbanyak: X teman → node [n1 n2 ...]" (sorted)
- "Tanpa teman: [n1 n2 ...] / tidak ada" (sorted)
- "Tepat 1 teman: [n1 n2 ...] / tidak ada" (sorted)

CONSTRAINTS:
- 1 ≤ n ≤ 10^4
- 0 ≤ m ≤ 10^5

SAMPLE INPUT 1:
5 5
1 2
1 3
2 3
2 4
3 5

SAMPLE OUTPUT 1:
Teman terbanyak: 3 teman → node 2 3
Tanpa teman: tidak ada
Tepat 1 teman: node 4 5

SAMPLE INPUT 2:
4 1
2 3

SAMPLE OUTPUT 2:
Teman terbanyak: 1 teman → node 2 3
Tanpa teman: node 1 4
Tepat 1 teman: node 2 3

NOTE: Hitung degree tiap node. Degree 0 = tanpa teman. Max degree = teman terbanyak.
      Node 2: teman {1,3,4} → degree 3. Node 3: teman {1,2,5} → degree 3.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
