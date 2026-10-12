/*
============================================================
📋 TUGAS 11: Membandingkan Empat Tie-Break
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Metodologi

PROBLEM:
Ambil soal 'hitung berapa rentang yang termuat di rentang lain'. Implementasikan
EMPAT varian tie-break saat l seri:
  (A) r menurun
  (B) r menaik
  (C) tanpa tie-break sama sekali
  (D) r menurun plus tambalan rentang identik
Bandingkan keempatnya dengan brute force O(n^2) pada 20.000 masukan acak, sekali
dengan koordinat 1..4 dan sekali dengan koordinat 1..10^9.
Laporkan persentase kegagalan masing-masing pada KEDUA rentang koordinat.

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Delapan persentase (empat varian kali dua rentang koordinat) plus penjelasan

CONSTRAINTS:
n <= 8 pada brute force

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
    // Hasil yang kamu cari: pada koordinat 10^9 keempat varian akan hampir sama-sama benar, pada koordinat 1..4 hanya satu yang bertahan. Inilah bukti empiris kenapa generator harus dirancang, bukan sekadar acak.

    return 0;
}
