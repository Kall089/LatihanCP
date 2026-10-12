/*
============================================================
📋 TUGAS 11: Largest Color Value in a Directed Graph
============================================================
Source: LC 1857
Difficulty: Hard
Topics: DP vektor 26 dimensi di DAG + deteksi siklus

PROBLEM:
Graf berarah N simpul; simpul i berwarna huruf c[i]. Nilai sebuah jalur adalah
banyak kemunculan TERBANYAK satu warna di sepanjang jalur itu. Cari nilai
terbesar di seluruh graf. Cetak -1 jika ada siklus.

INPUT FORMAT:
- Baris 1: N M
- Baris 2: string warna panjang N
- M baris: u v

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 4                    3
abaca
1 2
1 3
3 4
4 5
Penjelasan: jalur 1-3-4-5 berwarna a, a, c, a -> huruf 'a' muncul 3 kali.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    -1
aaa
1 2
2 3
3 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4 3                    4
aaaa
1 2
2 3
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[v][26]. Saat merelaksasi u -> v: dp[v][c] = max(dp[v][c], dp[u][c]),
    // lalu dp[v][warna(v)]++ tepat sekali saat v pertama dimasukkan hasil.
    // Memori 10^5 * 26 * 4 byte = ~10 MB, masih muat.
    // Siklus terdeteksi lewat Kahn seperti biasa.
    return 0;
}
