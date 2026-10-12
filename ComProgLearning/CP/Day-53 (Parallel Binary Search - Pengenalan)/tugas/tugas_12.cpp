/*
============================================================
📋 TUGAS 12: Runtuhnya Jembatan
============================================================
Source: Original
Difficulty: Hard
Topics: proses mundur

PROBLEM:
N pulau terhubung M jembatan. Selama T hari, setiap hari satu jembatan
RUNTUH. Untuk tiap query (u, v), cari hari terakhir di mana u dan v masih
terhubung (0 kalau sudah tidak terhubung sejak awal).

INPUT FORMAT:
- Baris pertama: N, M, T, Q
- M baris: u v
- T baris: indeks jembatan yang runtuh
- Q baris: u v

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, M, T, Q <= 2*10^5

SAMPLE INPUT 1:
3 3 2 1
1 2
2 3
1 3
3
1
1 3

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
    // DSU tidak mendukung PEMISAHAN. Tetapi kalau kamu memproses waktu secara MUNDUR, penghapusan jembatan menjadi PENAMBAHAN - dan DSU kembali berlaku. Trik yang sangat berguna.

    return 0;
}
