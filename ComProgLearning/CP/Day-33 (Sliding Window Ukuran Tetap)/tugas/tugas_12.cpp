/*
 * Day 20 — Sliding Window
 * File  : tugas_12.cpp
 * Topik : Sliding Window Median
 * Tingkat: Hard ★★★★★
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan dan integer K.
 * Untuk setiap window kontinu berukuran K, cetak MEDIAN window tersebut.
 *
 * Median:
 *   - Jika K ganjil: elemen tengah setelah window di-sort
 *   - Jika K genap: rata-rata dua elemen tengah (sebagai double)
 *
 * Pendekatan: pakai dua multiset:
 *   - lo: K/2 elemen terkecil (akses max via *lo.rbegin())
 *   - hi: sisanya (akses min via *hi.begin())
 *   Median = max(lo) untuk K ganjil, atau (max(lo)+min(hi))/2 untuk K genap.
 *
 * Saat slide:
 *   - insert A[R] ke salah satu set, balance ukuran
 *   - erase A[L] dari set yang sesuai, balance ukuran
 *
 * Alternatif: pakai policy-based tree (order_of_key). Atau pakai
 * priority queue dengan lazy deletion.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan
 * Output format : (N-K+1) median, dipisah spasi (presisi 1 desimal)
 * Constraints   : 1 ≤ K ≤ N ≤ 100.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 8 3                    1.0 -1.0 -1.0 3.0 5.0 6.0
 * 1 3 -1 -3 5 3 6 7
 *
 * Sample Input 2:        Sample Output 2:
 * 4 2                    2.5 4.5 7.0
 * 1 4 5 9
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: dua multiset, balance saat slide
    // Hati-hati: cout << fixed << setprecision(1) untuk output presisi

    return 0;
}
