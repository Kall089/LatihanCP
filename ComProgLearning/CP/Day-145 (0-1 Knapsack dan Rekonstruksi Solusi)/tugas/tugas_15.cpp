/*
============================================================
📋 TUGAS 15: Berapa Cara Mencapai Jumlah
============================================================
Source: Original
Difficulty: Hard
Topics: hitung cara, bukan maksimum

PROBLEM:
N barang dengan berat masing-masing. Hitung ada berapa CARA memilih
subhimpunan yang total beratnya TEPAT S. Cetak hasilnya modulo
1_000_000_007. Dua cara berbeda kalau himpunan indeks yang dipilih berbeda.

INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N berat

OUTPUT FORMAT:
- Satu bilangan mod 1e9+7

CONSTRAINTS:
- 1 <= N <= 500
- 1 <= S <= 10^5

SAMPLE INPUT 1:
4 5
1 2 3 2

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
    // Struktur rekurensnya IDENTIK dengan subset sum; yang berubah hanya operator penggabungnya dari OR/max menjadi penjumlahan. Pola 'ganti operator, dapatkan masalah berbeda' berlaku untuk hampir seluruh DP.

    return 0;
}
