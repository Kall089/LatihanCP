/*
============================================================
📋 TUGAS 12: Melanggar Strict Weak Ordering
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Keamanan komparator

PROBLEM:
Tulis komparator yang SENGAJA melanggar strict weak ordering (misalnya memakai <=),
lalu jalankan std::sort pada 100.000 elemen dengan hanya 3 nilai berbeda.
Kompilasi dua kali: sekali biasa, sekali dengan bendera -D_GLIBCXX_DEBUG.
Laporkan apa yang terjadi pada masing-masing.

INPUT FORMAT:
Bebas

OUTPUT FORMAT:
Laporan perilaku kedua kompilasi, plus penjelasan kenapa berbeda

CONSTRAINTS:
Pakai minimal 100.000 elemen agar std::sort benar-benar masuk ke jalur introsort

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
    // Bendera -D_GLIBCXX_DEBUG layak kamu ingat selamanya. Ia menangkap pelanggaran komparator, iterator tak sah, dan akses di luar batas pada container — kesalahan yang biasanya hanya muncul sebagai jawaban aneh.

    return 0;
}
