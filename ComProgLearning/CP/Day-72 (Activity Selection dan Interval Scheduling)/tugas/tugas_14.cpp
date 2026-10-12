/*
============================================================
📋 TUGAS 14: Membandingkan Empat Kriteria Greedy
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Metodologi verifikasi

PROBLEM:
Implementasikan EMPAT strategi untuk activity selection:
  (A) urut menurut waktu selesai
  (B) urut menurut waktu mulai
  (C) urut menurut durasi terpendek
  (D) urut menurut jumlah konflik paling sedikit
Bandingkan keempatnya dengan brute force 2^n pada masukan acak (n <= 16).
Laporkan berapa persen kasus masing-masing strategi gagal, dan simpan contoh
tandingan TERKECIL yang kamu temukan untuk B, C, dan D.

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Persentase kegagalan tiap strategi + contoh tandingan terkecil

CONSTRAINTS:
n <= 16 agar brute force cepat; koordinat kecil (misal 1..20) agar tumpang tindih sering terjadi

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
    // Koordinat KECIL sangat penting: dengan koordinat besar interval jarang bertabrakan dan semua strategi terlihat benar. Ini pelajaran umum tentang cara membuat generator stress test yang bagus.

    return 0;
}
