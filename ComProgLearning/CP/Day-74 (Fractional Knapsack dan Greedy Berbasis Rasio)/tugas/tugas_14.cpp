/*
============================================================
📋 TUGAS 14: Menemukan Batas Kegagalan Greedy
============================================================
Source: Latihan mandiri (eksperimen)
Difficulty: Medium
Topics: Intuisi kapan greedy benar

PROBLEM:
Jalankan eksperimen dari Tugas 09 dengan variasi berikut, dan catat bagaimana
persentase kegagalan greedy rasio berubah:
  (a) W jauh lebih besar dari total berat
  (b) semua berat sama
  (c) semua nilai sama
  (d) berat jauh lebih kecil dari W (misal w <= W/100)
Untuk setiap kasus, jelaskan MENGAPA persentasenya berubah seperti itu.

INPUT FORMAT:
Bebas — buat generator sendiri

OUTPUT FORMAT:
Empat persentase + penjelasan untuk masing-masing

CONSTRAINTS:
Gunakan minimal 10.000 kasus per varian agar angkanya stabil

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
    // Kasus (a) dan (d) seharusnya mendekati nol persen. Pikirkan apa yang hilang dari soal ketika 'sisa kapasitas yang terbuang' menjadi tidak berarti — itulah inti kenapa greedy gagal pada 0/1.

    return 0;
}
