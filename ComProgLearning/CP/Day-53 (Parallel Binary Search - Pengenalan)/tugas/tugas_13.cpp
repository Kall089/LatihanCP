/*
============================================================
📋 TUGAS 13: Ekspedisi Bertahap
============================================================
Source: Original
Difficulty: Hard
Topics: PBS + Dijkstra

PROBLEM:
Peta berupa graf berbobot dengan N simpul dan M sisi. Setiap hari selama T
hari, bobot satu sisi berkurang (menjadi lebih murah). Untuk tiap query
(u, v, B), cari hari keberapa biaya perjalanan terpendek dari u ke v
menjadi tidak melebihi B.

INPUT FORMAT:
- Baris pertama: N, M, T, Q
- M baris: u v w
- T baris: indeks sisi dan bobot barunya
- Q baris: u v B

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- N, M <= 1000
- T, Q <= 1000

SAMPLE INPUT 1:
2 1 1 1
1 2 10
1 5
1 2 7

SAMPLE OUTPUT 1:
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Setiap putaran butuh menjalankan Dijkstra beberapa kali. Hitung total biayanya DULU: log(T) putaran x (T update + Q kali Dijkstra) - apakah muat?

    return 0;
}
