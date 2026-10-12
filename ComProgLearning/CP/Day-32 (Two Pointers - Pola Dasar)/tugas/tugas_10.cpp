/*
 * Day 19 — Two Pointers
 * File  : tugas_10.cpp
 * Topik : Longest Mountain in Array
 * Tingkat: Medium
 * -----------------------------------------------
 * Sebuah "mountain" dalam array adalah subarray A[i..j] (i < j) yang:
 *   1. A[i] < A[i+1] < ... < A[peak] (naik)
 *   2. A[peak] > A[peak+1] > ... > A[j] (turun)
 *   3. Ada setidaknya satu elemen di kiri peak dan satu di kanan peak
 *   4. Panjang minimum mountain adalah 3
 *
 * Temukan panjang mountain terpanjang dalam array A.
 * Jika tidak ada mountain, output 0.
 *
 * Pendekatan Two Pointers:
 *   Untuk setiap kandidat peak (elemen yang lebih besar dari tetangga):
 *   - Dari peak, ekspansi ke kiri (L--) selama A[L-1] < A[L]
 *   - Dari peak, ekspansi ke kanan (R++) selama A[R] > A[R+1]
 *   - Panjang mountain = R - L + 1
 *
 * Pendekatan Alternatif (satu pass):
 *   - up[i] = panjang naik berakhir di i
 *   - down[i] = panjang turun mulai dari i
 *   - Untuk peak i: mountain = up[i] + down[i] - 1
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan bulat
 * Output format : Panjang mountain terpanjang (0 jika tidak ada)
 * Constraints   : 1 ≤ N ≤ 100.000
 *                 0 ≤ A[i] ≤ 10^8
 *
 * Sample Input 1:      Sample Output 1:
 * 8                    5
 * 2 1 4 7 3 2 5 1
 *
 * Sample Input 2:      Sample Output 2:
 * 5                    0
 * 1 2 3 4 5
 *
 * Sample Input 3:      Sample Output 3:
 * 7                    7
 * 1 3 5 7 5 3 1
 *
 * Sample Input 4:      Sample Output 4:
 * 3                    3
 * 0 2 0
 *
 * Penjelasan Sample 1:
 *   A=[2,1,4,7,3,2,5,1]
 *   Mountain 1: A[1..5]=[1,4,7,3,2] → peak=7 di index 3, panjang=5
 *   Mountain 2: A[5..7]=[2,5,1] → peak=5 di index 6, panjang=3
 *   Terpanjang: 5 ✓
 *
 * Penjelasan Sample 2:
 *   A=[1,2,3,4,5]: hanya naik, tidak pernah turun → tidak ada mountain → 0 ✓
 *
 * Penjelasan Sample 3:
 *   A=[1,3,5,7,5,3,1]: satu mountain besar panjang 7 ✓
 *
 * Hint:
 *   - Loop i dari 1 sampai n-2
 *   - Jika A[i] > A[i-1] && A[i] > A[i+1]: i adalah peak
 *   - Ekspansi L dan R dari i
 *   - Update ans dengan R - L + 1
 *   - Lanjutkan i dari R (skip bagian yang sudah diproses) untuk O(n)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
