/*
============================================================
📋 TUGAS 12: Menggabungkan dengan Biaya Berbeda
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Huffman termodifikasi

PROBLEM:
Ada n berkas berukuran a[i]. Menggabungkan dua berkas berukuran x dan y berbiaya
(x + y) * c, dengan c adalah bilangan tetap yang diberikan.
Selain itu, setiap berkas hasil gabungan dikenai biaya penyimpanan tetap sebesar d.
Cari total biaya minimum untuk menggabungkan semuanya menjadi satu.

INPUT FORMAT:
Baris 1: n, c, dan d
Baris 2: n ukuran a[i]

OUTPUT FORMAT:
Satu bilangan: total biaya minimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= c <= 10^9, 0 <= d <= 10^9, 1 <= a[i] <= 10^9

SAMPLE INPUT 1:
4 2 5
1 2 3 4

SAMPLE OUTPUT 1:
53
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perhatikan bahwa jumlah penggabungan SELALU n-1 apa pun urutannya. Apa artinya bagi suku d? Setelah menyadari itu, sisanya adalah Huffman biasa.

    return 0;
}
