/*
 * Day 19 — Two Pointers
 * File  : tugas_07.cpp
 * Topik : Two Sum II — Count ALL Pairs With Sum = K
 * Tingkat: Medium
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat (TIDAK harus sorted) dan target K.
 * Hitung jumlah pasangan NILAI UNIK (a, b) dengan a ≤ b dan a + b = K.
 * Dua pasangan dianggap sama jika nilai a dan b-nya sama (bukan indeks).
 *
 * Berbeda dengan tugas_01 yang menghitung pasangan berdasarkan indeks,
 * di sini kita hitung pasangan berdasarkan nilai unik.
 *
 * Pendekatan Two Pointers:
 *   1. Sort array
 *   2. L = 0, R = N-1
 *   3. Saat A[L]+A[R] == K:
 *      - Jika A[L] != A[R]: ini pasangan unik baru. ans++
 *        Skip semua A[L] yang sama, skip semua A[R] yang sama
 *      - Jika A[L] == A[R]: satu pasangan unik (nilai yang sama). ans++
 *        Stop (L dan R bertemu di tengah)
 *   4. Saat A[L]+A[R] < K: L++
 *   5. Saat A[L]+A[R] > K: R--
 *
 * Input format  : Baris 1: N K
 *                 Baris 2: N bilangan bulat
 * Output format : Satu bilangan: jumlah pasangan nilai unik
 * Constraints   : 2 ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 -2×10^9 ≤ K ≤ 2×10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5 6                  2
 * 1 2 3 4 5
 *
 * Sample Input 2:      Sample Output 2:
 * 6 5                  2
 * 1 1 2 3 4 5
 *
 * Sample Input 3:      Sample Output 3:
 * 4 10                 0
 * 1 2 3 4
 *
 * Penjelasan Sample 1:
 *   A=[1,2,3,4,5], K=6: pasangan nilai (1,5) dan (2,4) → 2 ✓
 *
 * Penjelasan Sample 2:
 *   A=[1,1,2,3,4,5], K=5: pasangan nilai (1,4) dan (2,3) → 2 ✓
 *   (1,4) muncul dua kali secara indeks, tapi hanya satu pasangan nilai)
 *
 * Bonus: Bagaimana jika K = 2 dan A = [1,1,1,1]?
 *   Pasangan nilai: (1,1) → 1 pasangan ✓
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
