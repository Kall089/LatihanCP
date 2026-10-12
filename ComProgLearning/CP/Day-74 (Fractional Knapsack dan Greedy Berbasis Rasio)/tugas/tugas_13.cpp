/*
============================================================
📋 TUGAS 13: Knapsack Berkelompok
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Group knapsack

PROBLEM:
Ada n barang yang dikelompokkan ke dalam m kelompok. Dari setiap kelompok kamu boleh
mengambil PALING BANYAK SATU barang. Kapasitas W. Cari nilai maksimum.

INPUT FORMAT:
Baris 1: n, m, dan W
n baris berikutnya: w[i], v[i], dan nomor kelompok g[i] (1 sampai m)

OUTPUT FORMAT:
Satu bilangan: nilai maksimum

CONSTRAINTS:
1 <= n <= 1000, 1 <= m <= n, 1 <= W <= 10^4, 1 <= w[i] <= 10^4, 1 <= v[i] <= 10^9

SAMPLE INPUT 1:
4 2 10
3 4 1
5 7 1
4 6 2
6 9 2

SAMPLE OUTPUT 1:
13
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perubahannya kecil tapi kritis: loop terluar menjadi KELOMPOK, bukan barang. Pikirkan di mana tepatnya loop kapasitas harus berada agar tidak lebih dari satu barang per kelompok terambil.

    return 0;
}
