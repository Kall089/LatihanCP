#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)
 * Latihan 6: Kamus Alien (Rekonstruksi Urutan Huruf)
 *
 * Diberikan N kata yang HANYA memakai huruf 'a'..'z' dan sudah terurut
 * menurut alfabet suatu bahasa asing (urutan hurufnya tidak diketahui).
 * Tentukan satu urutan huruf yang konsisten, memuat SEMUA huruf yang muncul,
 * leksikografis terkecil menurut alfabet Latin biasa jika ada beberapa pilihan.
 * Cetak "" (baris kosong) jika datanya tidak konsisten.
 *
 * Petunjuk model: bandingkan setiap dua kata bersebelahan, cari posisi huruf
 * pertama yang berbeda -> itu satu edge. Kalau kata panjang muncul sebelum
 * prefiksnya ("abcd" lalu "ab"), data tidak konsisten.
 *
 * Batas: 1 <= N <= 1000, panjang kata <= 20
 *
// Test Case 1:
// Input:
// 5
// wrt
// wrf
// er
// ett
// rftt
// Output:
// wertf
//
// Test Case 2 (tidak konsisten - prefiks di belakang):
// Input:
// 2
// abcd
// ab
// Output:
// (baris kosong)
//
// Test Case 3 (tidak ada batasan sama sekali):
// Input:
// 2
// zx
// zy
// Output:
// xyz
// (edge hanya x -> y; huruf z bebas, jadi ambil terkecil dulu)
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // 1. kumpulkan huruf yang muncul
    // 2. bangun edge dari pasangan kata bersebelahan
    // 3. Kahn leksikografis
    // 4. hasil.size() != jumlah huruf  =>  tidak konsisten
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
