/*
============================================================
📋 TUGAS 12: Dua Mesin dengan Tenggat
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Penjadwalan paralel

PROBLEM:
Ada n pekerjaan dan DUA mesin identik yang bekerja paralel. Pekerjaan ke-i butuh t[i]
waktu dan bertenggat d[i]. Setiap pekerjaan dikerjakan utuh oleh satu mesin.
Cari jumlah pekerjaan terlambat minimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i] dan d[i]

OUTPUT FORMAT:
Satu bilangan: jumlah pekerjaan terlambat minimum

CONSTRAINTS:
1 <= n <= 18, 1 <= t[i] <= 1000, 1 <= d[i] <= 10^4

SAMPLE INPUT 1:
3
3 3
3 3
3 3

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
    // Moore-Hodgson TIDAK berlaku untuk dua mesin. Batasan n <= 18 memberitahumu apa yang dimaksud. Pikirkan keadaan apa yang cukup untuk menggambarkan kedua mesin.

    return 0;
}
