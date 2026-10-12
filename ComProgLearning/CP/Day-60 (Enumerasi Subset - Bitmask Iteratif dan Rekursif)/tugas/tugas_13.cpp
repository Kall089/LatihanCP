/*
============================================================
📋 TUGAS 13: Count Hamiltonian Paths (Bitmask DP)
============================================================
Source: Original
Difficulty: Hard
Topics: bitmask DP, Hamiltonian path, counting

PROBLEM:
Diberikan graph berarah dengan n node (0-indexed) dan m edge.
Hitung berapa banyak Hamiltonian Path yang DIMULAI dari node 0
(mengunjungi setiap node tepat sekali, tidak harus kembali ke awal).

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (edge dari u ke v)

OUTPUT FORMAT:
- Satu integer: jumlah Hamiltonian Path yang dimulai dari node 0

CONSTRAINTS:
- 2 ≤ n ≤ 15
- 0 ≤ m ≤ n*(n-1)

SAMPLE INPUT 1:
4 6
0 1
0 2
1 2
1 3
2 3
3 0

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
3 6
0 1
1 0
0 2
2 0
1 2
2 1

SAMPLE OUTPUT 2:
2

NOTE: Untuk sample 1, 2 path: 0→1→2→3 dan 0→2→... (cek sendiri).
      
      Hint Bitmask DP:
        dp[mask][v] = jumlah cara mencapai node v dengan mengunjungi
                      tepat node-node yang aktif di mask, dimulai dari 0.
        Base: dp[1][0] = 1 (hanya node 0 dikunjungi, berakhir di 0)
        Transisi: dp[mask|(1<<u)][u] += dp[mask][v]
                  jika ada edge v→u dan bit u belum di mask.
        Jawaban: Σ dp[(1<<n)-1][v] untuk semua v.
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
