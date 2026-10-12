/*
============================================================
📋 TUGAS 14: Urutan Topologis dengan Prioritas Waktu
============================================================
Source: Varian scheduling
Difficulty: Hard
Topics: Kahn + heap berdasar kunci non-trivial

PROBLEM:
N tugas dengan durasi d_i, M ketergantungan. Satu pekerja mengerjakan satu
tugas pada satu waktu. Kerjakan sedemikian rupa sehingga JUMLAH waktu selesai
seluruh tugas minimum. Cetak jumlah waktu selesai tersebut, atau -1 jika ada
siklus.

INPUT FORMAT:
- Baris 1: N M
- Baris 2: d_1 .. d_N
- M baris: u v

OUTPUT FORMAT:
- satu bilangan (gunakan long long)

CONSTRAINTS:
- 1 <= N, M <= 2*10^5; 1 <= d_i <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 0                    12
5 2 1
Penjelasan: tanpa ketergantungan, kerjakan dari durasi terkecil: 1, 2, 5.
Waktu selesai 1, 3, 8 -> jumlah 12.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    9
3 3
1 2
Penjelasan: 1 wajib dulu -> selesai 3 dan 6 -> jumlah 9.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 2                    -1
1 2
2 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Kahn dengan min-heap berdasarkan durasi. Pikirkan baik-baik apakah
    // greedy ini benar-benar optimal -- dan cari counterexample kalau tidak.
    return 0;
}
