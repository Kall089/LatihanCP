/*
============================================================
📋 TUGAS 15: Bandingkan Empat Algoritma
============================================================
Source: Latihan sintesis (penutup Day 127)
Difficulty: Hard
Topics: memilih alat yang tepat

PROBLEM:
Diberikan graf berarah berbobot yang bobotnya BOLEH negatif, dan sebuah flag
di baris pertama yang menyatakan apakah graf dijamin DAG.
Tulis satu program yang:
  1. memilih algoritma yang TEPAT (Dijkstra / DP topologis / Bellman-Ford),
  2. mencetak nama algoritma yang dipilih,
  3. mencetak jarak terpendek 1 -> N,
  4. mencetak "SIKLUS NEGATIF" jika terdeteksi.

INPUT FORMAT:
- Baris 1: N M isDag   (isDag = 0 atau 1)
- M baris: u v w

OUTPUT FORMAT:
- Baris 1: DIJKSTRA / DP-DAG / BELLMAN-FORD
- Baris 2: jarak, atau -1, atau SIKLUS NEGATIF

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, |w| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 2 0                  DIJKSTRA
1 2 4                  6
2 3 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4 1                  DP-DAG
1 2 1                  -10
1 3 10
2 4 10
3 4 -20

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 3 0                  BELLMAN-FORD
1 2 1                  SIKLUS NEGATIF
2 3 -5
3 2 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Aturan pemilihan:
    //   semua w >= 0            -> DIJKSTRA      O(E log V)
    //   ada w < 0 tapi DAG      -> DP-DAG        O(V + E)
    //   ada w < 0 dan bersiklus -> BELLMAN-FORD  O(V * E), + deteksi siklus negatif
    // Ini adalah inti seluruh materi Day 120 dan Day 127 dalam satu program.
    return 0;
}
