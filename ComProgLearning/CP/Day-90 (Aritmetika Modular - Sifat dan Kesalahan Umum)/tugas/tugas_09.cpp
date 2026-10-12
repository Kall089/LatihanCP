/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_09.cpp
 * Topik : Hitung Subarray dengan Sum Habis Dibagi K
 * Tingkat: Medium ★★★★☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat (boleh negatif) dan bilangan K.
 * Hitung BANYAKNYA subarray kontinu (i..j) yang jumlahnya habis dibagi K.
 *
 * Idea kunci (gabungan prefix sum + residue class):
 *   sum(i..j) = pre[j] − pre[i-1]
 *   habis dibagi K  ⟺  pre[j] ≡ pre[i-1] (mod K)
 *
 * Jadi: hitung berapa banyak PASANGAN prefix yang punya residu sama!
 *   - Simpan cnt[r] = berapa banyak prefix dengan residu r
 *   - Inisialisasi cnt[0] = 1 (prefix kosong, agar subarray mulai dari
 *     index 1 ikut terhitung)
 *   - Untuk tiap prefix baru dengan residu r: jawaban += cnt[r], lalu cnt[r]++
 *
 * ⚠️ A[i] boleh negatif → residu HARUS dinormalisasi ke [0, K-1],
 *    kalau tidak, dua nilai yang sebenarnya kongruen akan dihitung
 *    sebagai residu berbeda (misal −2 dan 3 pada K=5).
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan A[i]
 * Output format : satu bilangan — jumlah subarray yang sum-nya habis dibagi K
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ K ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 (jawaban bisa mencapai ~2×10^10 → pakai long long)
 *
 * Sample Input 1:        Sample Output 1:
 * 6 5                    7
 * 4 5 0 -2 -3 1
 *
 * Sample Input 2:        Sample Output 2:
 * 3 3                    3
 * 1 2 3
 *
 * Sample Input 3:        Sample Output 3:
 * 3 5                    6
 * 5 5 5
 *
 * NOTE Sample 3: semua elemen kelipatan 5, jadi SEMUA C(3,1)+C(3,2)+C(3,3)
 *      = 3+2+1 = 6 subarray memenuhi.
 * NOTE Sample 1: jawaban 7 — kerjakan dan verifikasi sendiri.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan prefix sum modulo + counting residue class

    return 0;
}
