/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_03.cpp
 * Topik : Sisa Bagi Bilangan Raksasa oleh 3 dan 9
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan T bilangan bulat non-negatif, masing-masing berupa STRING
 * sepanjang sampai 100.000 digit. Untuk setiap bilangan, cetak dua nilai
 * dipisah spasi: sisa bagi oleh 3, dan sisa bagi oleh 9.
 *
 * Ada dua cara — kerjakan KEDUANYA lalu bandingkan:
 *   (a) Horner's rule: res = (res*10 + digit) % m
 *   (b) Sifat digit sum: karena 10 ≡ 1 (mod 3) dan 10 ≡ 1 (mod 9),
 *       maka N ≡ (jumlah semua digit N) (mod 3) dan (mod 9).
 *
 * Cara (b) menjelaskan MENGAPA aturan "habis dibagi 3 jika jumlah digitnya
 * habis dibagi 3" yang dipelajari di SD itu benar.
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: satu string bilangan per baris
 * Output format : T baris, masing-masing dua bilangan dipisah spasi
 * Constraints   : 1 ≤ T ≤ 100
 *                 1 ≤ panjang tiap bilangan ≤ 100.000
 *
 * Sample Input 1:                Sample Output 1:
 * 4                              0 0
 * 123456789                      0 0
 * 999999999999999999999          1 7
 * 7                              0 3
 * 111
 *
 * NOTE: 123456789 → jumlah digit = 45 → 45%3=0, 45%9=0.
 *       7 → 7%3=1, 7%9=7.
 *       111 → jumlah digit = 3 → 3%3=0, 3%9=3.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan Horner, lalu verifikasi dengan digit sum

    return 0;
}
