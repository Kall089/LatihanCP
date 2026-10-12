/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_11.cpp
 * Topik : Fibonacci ke-N untuk N ≤ 10^18 (Matrix Exponentiation)
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Hitung F(N) mod 10^9+7 dengan F(0)=0, F(1)=1, untuk N sampai 10^18.
 *
 * Iterasi O(N) dari tugas_06 sudah tidak mungkin. Gunakan
 * MATRIX EXPONENTIATION — binary exponentiation pada matriks 2×2:
 *
 *   ┌ F(n+1) ┐   ┌ 1  1 ┐^n   ┌ F(1) ┐
 *   │        │ = │      │   × │      │
 *   └ F(n)   ┘   └ 1  0 ┘     └ F(0) ┘
 *
 * Sehingga:
 *   ┌ 1  1 ┐^n   ┌ F(n+1)  F(n)   ┐
 *   │      │   = │                │
 *   └ 1  0 ┘     └ F(n)    F(n-1) ┘
 *
 * Jadi F(N) = elemen [0][1] dari matriks basis dipangkatkan N.
 *
 * Semua perkalian matriks dilakukan modulo 10^9+7. Tiap elemen < 10^9,
 * dan penjumlahan dua hasil kali = 2×10^18 → MASIH muat long long
 * (batas 9.22×10^18), tapi ambil mod setelah setiap penjumlahan agar aman.
 *
 * Ini adalah preview Day 149 (matrix exponentiation untuk linear recurrence).
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: satu bilangan N
 * Output format : T baris, masing-masing F(N) mod 10^9+7
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 0 ≤ N ≤ 10^18
 *
 * Sample Input 1:                Sample Output 1:
 * 6                              0
 * 0                              1
 * 1                              55
 * 10                             586268941
 * 50                             209783453
 * 1000000000000000000            480042305
 * 987654321987654321
 *
 * NOTE: Nilai untuk N=10 dan N=50 sama persis dengan tugas_06 —
 *       gunakan itu untuk memvalidasi implementasi matriksmu.
 *
 * HINT: Buat struct Mat2 dengan operator perkalian modular, lalu terapkan
 *       pola binary exponentiation yang sama (identity matrix sebagai "1").
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan matrix exponentiation 2x2 modular

    return 0;
}
