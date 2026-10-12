/*
============================================================
📋 TUGAS 11: IPO / Memaksimalkan Modal
============================================================
Source: LeetCode 502
Difficulty: Hard
Topics: Dua struktur, heap

PROBLEM:
Kamu punya modal awal C dan boleh menjalankan paling banyak K proyek. Proyek ke-i
membutuhkan modal minimal m[i] dan memberi keuntungan bersih p[i] yang langsung
menambah modalmu.
Cari modal akhir maksimum.

INPUT FORMAT:
Baris 1: n, K, dan C
n baris berikutnya: m[i] dan p[i]

OUTPUT FORMAT:
Satu bilangan: modal akhir maksimum

CONSTRAINTS:
1 <= n <= 10^5, 1 <= K <= 10^5, 0 <= C <= 10^9, 0 <= m[i], p[i] <= 10^9

SAMPLE INPUT 1:
3 2 0
0 1
1 2
1 3

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
    // Dua struktur bekerja sama: proyek diurutkan menurut modal minimum, dan heap menyimpan proyek yang sudah TERJANGKAU. Setiap kali modalmu naik, proyek baru menjadi terjangkau.

    return 0;
}
