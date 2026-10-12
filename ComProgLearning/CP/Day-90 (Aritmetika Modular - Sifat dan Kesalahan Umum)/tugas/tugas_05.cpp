/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_05.cpp
 * Topik : Rotasi Array Melingkar (Modulo untuk Index)
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N elemen (0-indexed) dan Q query.
 * Setiap query berisi bilangan bulat K (BISA NEGATIF), yang berarti:
 * "geser array ke KANAN sebanyak K posisi secara melingkar".
 *
 * Untuk setiap query, cetak elemen yang berada di INDEX 0 setelah rotasi.
 *
 * Setelah rotasi kanan sebanyak K, elemen di index 0 adalah A[(0 - K) mod N],
 * yaitu A[((-K) % N + N) % N].
 *
 * ⚠️ Ini adalah kasus di mana modulo negatif menyebabkan CRASH, bukan
 * sekadar jawaban salah — index array negatif = undefined behavior.
 *
 * Catatan: rotasi tiap query bersifat INDEPENDEN (selalu dari array asli).
 *
 * Input format  : Baris 1: N dan Q
 *                 Baris 2: N bilangan A[i]
 *                 Q baris berikutnya: satu bilangan K
 * Output format : Q baris, masing-masing elemen di index 0 setelah rotasi
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ Q ≤ 200.000
 *                 -10^18 ≤ K ≤ 10^18
 *                 -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 5 5                    10
 * 10 20 30 40 50         50
 * 0                      20
 * 1                      10
 * -1                     40
 * 5
 * 7
 *
 * NOTE: K=0  → array tetap, index 0 = 10.
 *       K=1  → [50,10,20,30,40], index 0 = 50.
 *       K=-1 → geser kiri 1 → [20,30,40,50,10], index 0 = 20.
 *       K=5  → satu putaran penuh, kembali ke semula = 10.
 *       K=7  → sama dengan K=2 → [40,50,10,20,30], index 0 = 40.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan — hitung index dengan normalisasi modulo N

    return 0;
}
