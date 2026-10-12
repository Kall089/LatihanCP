/*
============================================================
📋 TUGAS 12: Deteksi Deadlock
============================================================
Source: Klasik (sistem operasi)
Difficulty: Hard
Topics: model wait-for graph, siklus berarah

PROBLEM:
Ada P proses dan R resource. Diberi daftar "proses p MEMEGANG resource r" dan
"proses p MENUNGGU resource r". Bangun wait-for graph antar proses (p menunggu
q jika p menunggu resource yang dipegang q) dan tentukan apakah terjadi
deadlock. Jika ya, cetak satu himpunan proses yang terlibat, terurut menaik.

INPUT FORMAT:
- Baris 1: P R H W
- H baris: p r   (p memegang r)
- W baris: p r   (p menunggu r)

OUTPUT FORMAT:
- "AMAN", atau "DEADLOCK" lalu daftar prosesnya

CONSTRAINTS:
- 1 <= P, R <= 10^5; H, W <= 2*10^5; setiap resource dipegang <= 1 proses

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
2 2 2 2                DEADLOCK
1 1                    1 2
2 2
1 2
2 1

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 2 2 1                AMAN
1 1
2 2
1 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 3 3 3                DEADLOCK
1 1                    1 2 3
2 2
3 3
1 2
2 3
3 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Proses yang TIDAK keluar dari Kahn adalah yang terkurung (atau bergantung
    // pada yang terkurung). Untuk himpunan siklus murni, saring lagi.
    return 0;
}
