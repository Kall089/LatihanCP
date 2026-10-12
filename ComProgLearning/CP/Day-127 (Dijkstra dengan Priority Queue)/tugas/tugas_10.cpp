/*
============================================================
📋 TUGAS 10: Node Splitting (Biaya Melewati Simpul)
============================================================
Source: Varian klasik
Difficulty: Medium
Topics: transformasi graf

PROBLEM:
Graf berarah; biaya bukan hanya pada edge, tetapi juga pada SIMPUL (biaya
melewati simpul v adalah c[v], termasuk simpul awal dan akhir). Cari total
biaya minimum dari 1 ke N.

INPUT FORMAT:
- Baris 1: N M
- Baris 2: c_1 .. c_N
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan, atau -1

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= c, w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 2                    16
1 10 1
1 2 2
2 3 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    7
1 10 1
1 2 2
2 3 2
1 3 5

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 0                    -1
5 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Cara termudah: masukkan c[v] ke dalam relaksasi -> nd = d + w + c[v],
    // lalu inisialisasi dist[1] = c[1].
    // Cara umum (node splitting): pecah v menjadi v_in dan v_out dengan edge
    // v_in -> v_out berbobot c[v]. Berguna kalau simpul punya KAPASITAS.
    return 0;
}
