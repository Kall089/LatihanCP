/*
============================================================
📋 TUGAS 10: Memory Comparison — Adj List vs Adj Matrix
============================================================
Source: Original
Difficulty: Medium
Topics: adjacency list, adjacency matrix, memory analysis

PROBLEM:
Untuk T test case, masing-masing berupa graph dengan V node dan E edge,
hitung perkiraan penggunaan memori (dalam bytes) menggunakan formula:
  - Adj List:   V×24 + 2×E×4  bytes  (V header vector + 2E int entries)
  - Adj Matrix: V×V×4          bytes  (V^2 integer entries)
Cetak mana yang lebih hemat. Jika sama, cetak "SAMA".

INPUT FORMAT:
- Baris 1: integer T
- T baris berikutnya: dua integer V dan E

OUTPUT FORMAT:
- T baris: "V=X E=Y: List=LB Matrix=MB → [List/Matrix/SAMA] lebih hemat"

CONSTRAINTS:
- 1 ≤ T ≤ 100
- 1 ≤ V ≤ 10^6
- 0 ≤ E ≤ V×(V-1)/2

SAMPLE INPUT 1:
3
100 500
1000 499000
50000 200

SAMPLE OUTPUT 1:
V=100 E=500: List=6400 Matrix=40000 → List lebih hemat
V=1000 E=499000: List=4016000 Matrix=4000000 → Matrix lebih hemat
V=50000 E=200: List=1201600 Matrix=10000000000 → List lebih hemat

NOTE: Untuk V=100, E=500:
        List  = 100×24 + 2×500×4 = 2400+4000 = 6400 bytes
        Matrix = 100×100×4 = 40000 bytes → List lebih hemat.
      Titik impas (break-even): List=Matrix → V×24+8×E = 4×V^2
        → E = (4V^2 - 24V) / 8 ≈ V^2/2 untuk V besar.
      Gunakan long long untuk menghindari overflow pada V besar!
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll V, E;
        cin >> V >> E;

        ll listMem   = V * 24 + 2 * E * 4;
        ll matrixMem = V * V * 4;

        string winner;
        if (listMem < matrixMem)      winner = "List";
        else if (matrixMem < listMem) winner = "Matrix";
        else                          winner = "SAMA";

        cout << "V=" << V << " E=" << E
             << ": List=" << listMem
             << " Matrix=" << matrixMem
             << " → ";
        if (winner == "SAMA") cout << "SAMA\n";
        else cout << winner << " lebih hemat\n";
    }
    return 0;
}
