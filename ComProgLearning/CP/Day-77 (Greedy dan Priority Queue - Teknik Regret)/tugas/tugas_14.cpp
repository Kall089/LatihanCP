/*
============================================================
📋 TUGAS 14: Menemukan Batas Regret
============================================================
Source: Latihan mandiri (esai + kode)
Difficulty: Hard
Topics: Metodologi

PROBLEM:
Untuk setiap varian berikut, tentukan apakah teknik regret masih BENAR. Buktikan
kalau ya, dan berikan contoh tandingan kalau tidak.

(1) deadline + durasi, maksimalkan JUMLAH kursus
(2) deadline + durasi, maksimalkan TOTAL NILAI
(3) deadline + durasi seragam, maksimalkan TOTAL KEUNTUNGAN
(4) deadline + durasi seragam pada M mesin, maksimalkan keuntungan
(5) dua sumber daya, maksimalkan jumlah barang
(6) isi ulang bahan bakar, minimalkan pemberhentian

Untuk masing-masing, jawab juga: apakah invarian 'di antara himpunan berukuran
maksimum, sumber daya terpakai minimum' masih bisa dirumuskan?

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Enam jawaban (BENAR + bukti, atau SALAH + contoh tandingan)

CONSTRAINTS:
n <= 8 pada brute force

SAMPLE INPUT 1:
(tidak ada — tugas terbuka)

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
    // Penyaring paling andal: regret bekerja kalau keadaan bisa diringkas menjadi SATU angka yang bisa dibandingkan. Begitu ada dua besaran yang bersaing, regret runtuh dan biasanya DP-lah jawabannya.

    return 0;
}
