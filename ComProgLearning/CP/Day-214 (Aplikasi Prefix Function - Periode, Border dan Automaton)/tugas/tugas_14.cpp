/*
============================================================
📋 TUGAS 14: Tembok Kubus
============================================================
Source: CF 471D
Difficulty: Hard
Topics: pi pada array selisih

PROBLEM:
Sebuah tembok direpresentasikan sebagai barisan tinggi a[1..n]. Sebuah pola
tembok b[1..m] dianggap cocok pada suatu posisi jika bentuknya sama, tanpa
peduli ketinggian absolutnya (seluruh potongan boleh digeser naik/turun).
Hitung berapa banyak posisi yang cocok.

INPUT FORMAT:
- Baris pertama: n dan m
- Baris kedua: n bilangan a[i]
- Baris ketiga: m bilangan b[i]

OUTPUT FORMAT:
- Satu bilangan: banyaknya posisi cocok

CONSTRAINTS:
- 1 <= n, m <= 2 * 10^5
- 1 <= a[i], b[i] <= 10^9

SAMPLE INPUT 1:
5 3
2 3 4 3 2
3 4 3

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
    // Bekerja pada array SELISIH d[i] = a[i+1] - a[i]. Tangani kasus m == 1 secara terpisah.

    return 0;
}
