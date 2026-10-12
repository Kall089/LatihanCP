/*
============================================================
📋 TUGAS 14: Mengurutkan Pecahan
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Komparator rasio yang aman

PROBLEM:
Diberikan n pecahan p[i]/q[i]. Urutkan menaik. Kalau dua pecahan bernilai SAMA,
yang penyebutnya lebih kecil lebih dulu; kalau penyebutnya juga sama, yang nomor
urutnya lebih kecil lebih dulu.
Cetak nomor urut (1-based) sesuai hasil pengurutan.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: p[i] dan q[i]

OUTPUT FORMAT:
Satu baris berisi n nomor urut

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= p[i], q[i] <= 10^9

SAMPLE INPUT 1:
4
1 2
2 4
1 3
3 4

SAMPLE OUTPUT 1:
3 1 2 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bandingkan dengan perkalian silang, bukan pembagian (Day 74). Perkaliannya mencapai 10^18 — pertimbangkan __int128. Perhatikan juga bahwa 1/2 dan 2/4 bernilai sama, dan tie-break-nya penting.

    return 0;
}
