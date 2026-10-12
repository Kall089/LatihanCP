/*
============================================================
📋 TUGAS 15: Tournament Ranking (Tuple Multi-Sort)
============================================================
Source: Original
Difficulty: Hard
Topics: tuple, vector, multi-criteria sort, string

PROBLEM:
Dalam sebuah tournament programming, N tim berkompetisi.
Setiap tim punya: nama, jumlah soal solved, dan total penalty time.

Ranking ditentukan oleh:
1. Solved TERBANYAK dulu (descending)
2. Jika solved sama, penalty TERKECIL dulu (ascending)
3. Jika solved dan penalty sama, nama LEXICOGRAPHIC (ascending)

Cetak ranking tim dari peringkat 1 sampai N.
Format output: "rank. nama solved penalty"

INPUT:
- Baris pertama: integer N
- N baris berikutnya: nama (string) solved (int) penalty (int)

OUTPUT:
- N baris: "rank. nama solved penalty"

CONSTRAINTS:
- 1 ≤ N ≤ 100,000
- 1 ≤ |nama| ≤ 20 (tanpa spasi)
- 0 ≤ solved ≤ 15
- 0 ≤ penalty ≤ 100,000

SAMPLE INPUT:
5
TeamAlpha 5 120
TeamBeta 5 100
TeamGamma 4 50
TeamDelta 5 100
TeamEpsilon 3 200

SAMPLE OUTPUT:
1. TeamBeta 5 100
2. TeamDelta 5 100
3. TeamAlpha 5 120
4. TeamGamma 4 50
5. TeamEpsilon 3 200

NOTE: TeamBeta dan TeamDelta sama-sama 5 solved, 100 penalty.
      TeamBeta < TeamDelta secara lexicographic, jadi rank lebih tinggi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Simpan tuple(-solved, penalty, nama) lalu sort ascending

    return 0;
}
