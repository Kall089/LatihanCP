/*
============================================================
📋 TUGAS 02: Memulihkan Potongan Awal
============================================================
Source: Cutting Sticks Pre-split
Difficulty: Medium
Topics: Knuth Optimization, Reduction to Sequential Merging

PROBLEM:
Sebuah pita panggung panjang L sudah terpotong di posisi B (0 < B < L),
membagi pita menjadi dua bagian independen: [0, B] dan [B, L].
Biaya pemotongan awal di titik B tidak dihitung.
Terdapat M titik potong wajib lainnya yang terurut ketat (semua berbeda dari B).
Masing-masing titik potong wajib harus dieksekusi dengan biaya sama dengan panjang potongan pita saat dipotong.
Karena titik B sudah memotong pita secara fisik di awal, pemotongan di sisi kiri B tidak mempengaruhi sisi kanan B!

Tentukan TOTAL BIAYA LANJUTAN MINIMUM untuk memotong seluruh M titik tersebut!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat L, B, dan M.
Baris kedua berisi M bilangan bulat titik potong wajib terurut menaik (boleh kosong jika M = 0).

OUTPUT FORMAT:
Satu baris berisi total biaya lanjutan minimum.

CONSTRAINTS:
1 < B < L <= 1.000.000.000
0 <= M <= 1998
Setiap titik potong berada di (0, L) dan tidak sama dengan B.

SAMPLE INPUT 1:
10 5 2
2 8

SAMPLE OUTPUT 1:
10
(Bagian [0, 5] dipotong di 2: biaya 5.
 Bagian [5, 10] dipotong di 8: biaya 5. Total = 10.)

SAMPLE INPUT 2:
10 5 0

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll l, b;
    int m;
    if (!(cin >> l >> b >> m)) return 0;

    // TODO: Selesaikan dua submasalah independen dengan Knuth Optimization

    return 0;
}
