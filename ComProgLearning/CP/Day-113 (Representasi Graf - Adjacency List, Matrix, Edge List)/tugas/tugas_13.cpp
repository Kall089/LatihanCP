/*
============================================================
📋 TUGAS 13: Graph Isomorphism Check (Necessary Conditions)
============================================================
Source: Original
Difficulty: Medium
Topics: degree sequence, graph isomorphism, necessary conditions

PROBLEM:
Diberikan dua graph tidak berarah G1 dan G2, masing-masing dengan n node.
Cek apakah kedua graph MUNGKIN isomorfik dengan memeriksa kondisi PERLU
(bukan kondisi cukup):
  1. Jumlah node sama
  2. Jumlah edge sama
  3. Degree sequence (sorted) sama
Jika semua terpenuhi: "POSSIBLY ISOMORPHIC"
Jika ada yang gagal: "NOT ISOMORPHIC" beserta alasannya.

INPUT FORMAT:
- Baris 1: integer n (berlaku untuk G1 dan G2)
- Baris 2: integer m1 (jumlah edge G1)
- m1 baris berikutnya: dua integer u v (edge G1)
- Baris berikutnya: integer m2 (jumlah edge G2)
- m2 baris berikutnya: dua integer u v (edge G2)

OUTPUT FORMAT:
- "G1: V=n, E=m1, degree=[d1,d2,...]" (sorted ascending)
- "G2: V=n, E=m2, degree=[d1,d2,...]" (sorted ascending)
- "POSSIBLY ISOMORPHIC" atau "NOT ISOMORPHIC: [alasan]"

CONSTRAINTS:
- 1 ≤ n ≤ 10^4
- 0 ≤ m1, m2 ≤ 10^5

SAMPLE INPUT 1:
3
3
1 2
2 3
1 3
3
1 2
1 3
2 3

SAMPLE OUTPUT 1:
G1: V=3, E=3, degree=[2,2,2]
G2: V=3, E=3, degree=[2,2,2]
POSSIBLY ISOMORPHIC

SAMPLE INPUT 2:
4
3
1 2
2 3
3 4
3
1 2
1 3
1 4

SAMPLE OUTPUT 2:
G1: V=4, E=3, degree=[1,1,1,2] (erratum: actual [1,1,1,2] → path graph)
G2: V=4, E=3, degree=[1,1,1,3] (star graph)
NOT ISOMORPHIC: degree sequence berbeda

NOTE: Degree sequence G1 (path 1-2-3-4): [1,1,2,2] bukan [1,1,1,2].
      Degree sequence G2 (star, center=1): [1,1,1,3].
      [1,1,2,2] ≠ [1,1,1,3] → NOT ISOMORPHIC.
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
