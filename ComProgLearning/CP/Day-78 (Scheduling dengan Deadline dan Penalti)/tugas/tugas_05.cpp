/*
============================================================
📋 TUGAS 05: Tenggat dengan Prasyarat
============================================================
Source: 1 | prec | Lmax
Difficulty: Hard
Topics: Modifikasi tenggat + EDF

PROBLEM:
Ada n pekerjaan pada satu mesin dan m aturan prasyarat (a sebelum b), dijamin tanpa
siklus. Minimalkan keterlambatan terbesar.

INPUT FORMAT:
Baris 1: n dan m
n baris berikutnya: t[i] dan d[i]
m baris berikutnya: a dan b (1-based)

OUTPUT FORMAT:
Satu bilangan (boleh negatif)

CONSTRAINTS:
1 <= n <= 2*10^5, 0 <= m <= 2*10^5, 1 <= t[i] <= 10^9, 1 <= d[i] <= 10^18

SAMPLE INPUT 1:
3 1
3 6
2 8
1 9
2 1

SAMPLE OUTPUT 1:
-1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tenggat efektif: d[a] = min(d[a], d_efektif[b] - t[b]). Proses graf ke arah TERBALIK. Setelah itu prasyarat bisa diabaikan sepenuhnya — buktikan kenapa.

    return 0;
}
