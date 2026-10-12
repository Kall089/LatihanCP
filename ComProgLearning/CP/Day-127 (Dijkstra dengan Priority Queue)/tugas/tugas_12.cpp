/*
============================================================
📋 TUGAS 12: K-Shortest Path
============================================================
Source: Klasik (varian Dijkstra)
Difficulty: Hard
Topics: relaksasi berulang terbatas

PROBLEM:
Graf berarah berbobot positif. Cari panjang jalur terpendek KE-K dari 1 ke N
(jalur boleh mengulang simpul; jalur berbeda dihitung terpisah meskipun
panjangnya sama). Cetak -1 jika kurang dari K jalur.

INPUT FORMAT:
- Baris 1: N M K
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 1000, 1 <= M <= 10^5, 1 <= K <= 100

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 5 2                  3
1 2 1
2 4 2
1 3 1
3 4 2
1 4 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 5 3                  5
1 2 1
2 4 2
1 3 1
3 4 2
1 4 5

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1 2                  -1
1 2 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Dijkstra tanpa "sekali final": izinkan setiap simpul dipop sampai K kali.
    // Simpan cnt[v]; kalau cnt[v] >= K, abaikan. Jawaban = jarak pada saat
    // simpul N dipop untuk ke-K kalinya.
    return 0;
}
