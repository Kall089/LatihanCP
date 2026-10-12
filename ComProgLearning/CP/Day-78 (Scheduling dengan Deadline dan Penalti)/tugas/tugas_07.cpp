/*
============================================================
📋 TUGAS 07: Scheduling to Minimize Lateness
============================================================
Source: Latihan mandiri
Difficulty: Easy
Topics: EDF + rekonstruksi

PROBLEM:
Sama seperti Tugas 01, tetapi cetak juga URUTAN pengerjaan (nomor pekerjaan 1-based)
yang mencapai keterlambatan terbesar minimum. Kalau ada beberapa urutan yang sah,
cetak yang nomor pekerjaannya lebih kecil lebih dulu saat tenggatnya sama.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i] dan d[i]

OUTPUT FORMAT:
Baris 1: keterlambatan terbesar minimum
Baris 2: n nomor pekerjaan sesuai urutan

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= t[i] <= 10^9, 1 <= d[i] <= 10^18

SAMPLE INPUT 1:
3
3 6
2 8
1 9

SAMPLE OUTPUT 1:
-3
1 2 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tie-break nomor pekerjaan membuat keluarannya deterministik (Day 76). Tanpa itu jawabanmu bisa berbeda dari juri meski nilainya benar.

    return 0;
}
