/*
============================================================
📋 TUGAS 12: Runtuhnya Jembatan
============================================================
Source: Original
Difficulty: Hard
Topics: balik waktu

PROBLEM:
N pulau terhubung M jembatan. Selama T hari, setiap hari satu jembatan
runtuh. Setelah setiap hari, cetak banyaknya komponen.

INPUT FORMAT:
- Baris pertama: N, M, T
- M baris: u v
- T baris: indeks jembatan yang runtuh

OUTPUT FORMAT:
- T baris

CONSTRAINTS:
- 1 <= N, M, T <= 2*10^5

SAMPLE INPUT 1:
3 3 2
1 2
2 3
1 3
3
1

SAMPLE OUTPUT 1:
1
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // DSU tidak bisa memisahkan. Proses MUNDUR: mulai dari keadaan akhir, tambahkan jembatan kembali dalam urutan terbalik.

    return 0;
}
