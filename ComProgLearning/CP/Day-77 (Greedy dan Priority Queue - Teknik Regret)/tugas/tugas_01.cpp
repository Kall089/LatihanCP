/*
============================================================
📋 TUGAS 01: Course Schedule III
============================================================
Source: LeetCode 630
Difficulty: Medium
Topics: Regret deadline+durasi

PROBLEM:
Ada n kursus; kursus ke-i butuh t[i] hari dan harus selesai paling lambat hari d[i].
Hanya satu kursus dikerjakan pada satu waktu. Cari jumlah kursus maksimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i] dan d[i]

OUTPUT FORMAT:
Satu bilangan: jumlah kursus maksimum

CONSTRAINTS:
1 <= n <= 10^4, 1 <= t[i] <= 10^4, 1 <= d[i] <= 10^4

SAMPLE INPUT 1:
4
100 200
200 1300
1000 1250
2000 3200

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urut tenggat menaik, ambil semua, batalkan durasi TERBESAR saat melanggar. MAX-heap.

    return 0;
}
