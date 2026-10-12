/*
============================================================
📋 TUGAS 12: Jumlah Cara Memilih Interval
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: DP menghitung, bukan mengoptimalkan

PROBLEM:
Diberikan n interval [l, r] (semua berbeda). Hitung BANYAKNYA himpunan bagian tak
kosong yang seluruh anggotanya saling lepas. Interval tertutup: bersentuhan di ujung
dianggap bentrok. Cetak hasilnya modulo 10^9+7.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: banyaknya himpunan bagian modulo 10^9+7

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= l <= r <= 10^9

SAMPLE INPUT 1:
3
1 2
3 4
1 4

SAMPLE OUTPUT 1:
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kerangka DP-nya sama dengan Exercise 5, tetapi max diganti penjumlahan. Perhatikan bahwa dp harus mendefinisikan 'himpunan yang berakhir tepat di sini' agar tidak terhitung ganda.

    return 0;
}
