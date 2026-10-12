/*
============================================================
📋 TUGAS 11: Kecepatan Rata-rata Maksimum pada Graf
============================================================
Source: Original
Difficulty: Hard
Topics: rasio pada siklus

PROBLEM:
Diberikan graf berarah dengan N simpul dan M sisi, sisi ke-i punya
keuntungan p[i] dan waktu t[i]. Cari SIKLUS yang memaksimalkan
(jumlah keuntungan) / (jumlah waktu). Cetak 6 desimal, atau -1 kalau tidak
ada siklus.

INPUT FORMAT:
- Baris pertama: N dan M
- M baris: u, v, p, t

OUTPUT FORMAT:
- Satu bilangan, 6 desimal, atau -1

CONSTRAINTS:
- 1 <= N <= 1000
- 1 <= M <= 5000

SAMPLE INPUT 1:
3 3
1 2 5 1
2 3 5 1
3 1 5 1

SAMPLE OUTPUT 1:
5.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ini minimum ratio cycle. Transformasi p - x*t, lalu cek apakah ada siklus POSITIF dengan Bellman-Ford (Day 129). Menggabungkan hari ini dengan materi graf.

    return 0;
}
