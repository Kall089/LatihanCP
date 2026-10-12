/*
============================================================
📋 TUGAS 05: Advertisement / Reservoir
============================================================
Source: Codeforces-style
Difficulty: Medium
Topics: Regret pada kapasitas

PROBLEM:
Ada n permintaan; permintaan ke-i datang pada waktu t[i] dan membutuhkan c[i] unit
sumber daya sampai selesai pada waktu e[i]. Kapasitas total adalah C.
Kamu boleh menolak permintaan. Maksimalkan JUMLAH permintaan yang diterima.

INPUT FORMAT:
Baris 1: n dan C
n baris berikutnya: t[i], e[i], dan c[i]

OUTPUT FORMAT:
Satu bilangan: jumlah permintaan maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= C <= 10^9, 1 <= t[i] < e[i] <= 10^9, 1 <= c[i] <= C

SAMPLE INPUT 1:
3 10
1 5 6
2 6 5
3 7 4

SAMPLE OUTPUT 1:
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
    // Perhatikan bahwa kapasitas dibebaskan kembali saat permintaan selesai. Apakah regret masih berlaku ketika sumber daya bisa kembali? Uji dugaanmu dengan brute force sebelum percaya.

    return 0;
}
