/*
============================================================
📋 TUGAS 03: Mengukur Tingkat Kegagalan
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Metodologi

PROBLEM:
Ukur persentase kegagalan enam klaim greedy berikut pada 20.000 masukan acak kecil
(bandingkan dengan brute force):
  (1) knapsack 0/1, rasio tertinggi
  (2) tukar uang, koin terbesar
  (3) interval saling lepas, terpendek dulu
  (4) interval saling lepas, mulai paling awal
  (5) menggabungkan tumpukan, urut lalu berurutan
  (6) antrean bermodal, urut m menurun (Day 76)
Laporkan keenam persentase, lalu untuk masing-masing hitung: kalau kamu mengujinya
pada LIMA sampel, berapa peluang kamu keliru menyimpulkan bahwa ia benar?

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Enam persentase kegagalan plus enam peluang keliru

CONSTRAINTS:
Nilai kecil (1..12), ukuran kecil (1..8)

SAMPLE INPUT 1:
(tidak ada — eksperimen)

SAMPLE OUTPUT 1:
(tidak ada)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Rumus peluangnya sederhana: (1 - p) pangkat 5. Untuk p = 12 persen hasilnya sekitar 53 persen. Angka itu layak kamu ingat: lima sampel tidak membuktikan apa pun.

    return 0;
}
