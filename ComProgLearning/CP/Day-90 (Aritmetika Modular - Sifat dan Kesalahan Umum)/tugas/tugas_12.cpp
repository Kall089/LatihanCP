/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_12.cpp
 * Topik : Hitung Pasangan dengan Jumlah Habis Dibagi K
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat (boleh negatif) dan bilangan K.
 * Hitung banyaknya pasangan indeks (i, j) dengan i < j sedemikian sehingga
 * (A[i] + A[j]) habis dibagi K.
 *
 * Brute force O(N²) akan TLE untuk N = 200.000.
 *
 * Idea — RESIDUE CLASS PAIRING:
 *   (A[i] + A[j]) ≡ 0 (mod K)  ⟺  r_j ≡ (K − r_i) mod K
 *   dengan r = A mod K yang sudah dinormalisasi ke [0, K-1].
 *
 *   Hitung cnt[r] = berapa elemen dengan residu r. Lalu:
 *     - residu 0 berpasangan dengan residu 0    → C(cnt[0], 2)
 *     - jika K genap: residu K/2 dengan K/2     → C(cnt[K/2], 2)
 *     - untuk r = 1 .. (K-1)/2                  → cnt[r] × cnt[K-r]
 *
 * ⚠️ Jangan double-count: pasangkan r dengan K−r hanya SEKALI
 *    (iterasi r hanya sampai separuh).
 * ⚠️ A[i] negatif → normalisasi residu, kalau tidak index cnt[] negatif.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan A[i]
 * Output format : satu bilangan — jumlah pasangan
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ K ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 (jawaban bisa ~2×10^10 → long long)
 *
 * Sample Input 1:        Sample Output 1:
 * 5 3                    4
 * 1 2 3 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 4 4                    6
 * 2 2 2 2
 *
 * Sample Input 3:        Sample Output 3:
 * 3 5                    0
 * 1 1 1
 *
 * NOTE Sample 1: pasangan valid (1,2)→3, (1,5)→6, (2,4)→6, (4,5)→9 = 4 pasang.
 * NOTE Sample 2: semua 2+2=4 habis dibagi 4 → C(4,2) = 6 pasang.
 *      Perhatikan: 2 adalah K/2 dengan K genap — kasus yang sering terlewat.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan counting residue class + pairing r dengan K-r

    return 0;
}
