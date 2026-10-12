/*
============================================================
📋 TUGAS 09: Membandingkan Empat Strategi Knapsack
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Metodologi

PROBLEM:
Implementasikan EMPAT strategi untuk 0/1 knapsack:
  (A) greedy rasio nilai/berat tertinggi
  (B) greedy nilai tertinggi
  (C) greedy berat teringan
  (D) DP (jawaban benar)
Bandingkan A, B, C terhadap D pada 20.000 masukan acak dan laporkan persentase
kegagalan masing-masing, plus contoh tandingan TERKECIL untuk tiap strategi.

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Tiga persentase kegagalan + tiga contoh tandingan terkecil

CONSTRAINTS:
n <= 8, w <= 12, v <= 20, W <= 25 agar brute force cepat dan tabrakan sering

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
    // Angka untuk strategi A sekitar 11-12 persen. Setelah tahu itu, renungkan: kalau kamu menguji ide greedy pada 5 sampel dan semuanya lolos, peluangnya sekitar 53 persen meski greedy-nya salah. Lima sampel tidak membuktikan apa pun.

    return 0;
}
