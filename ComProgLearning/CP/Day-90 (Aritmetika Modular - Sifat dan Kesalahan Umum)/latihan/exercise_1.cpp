/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_1.cpp
 * Topik : Jumlah & Hasil Kali Array Modulo M (Warm-up)
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat non-negatif dan sebuah modulus M.
 * Hitung dua nilai:
 *   1. (A[0] + A[1] + ... + A[N-1]) mod M
 *   2. (A[0] × A[1] × ... × A[N-1]) mod M
 *
 * Nilai asli bisa jauh melebihi kapasitas long long, jadi WAJIB mengambil
 * mod di SETIAP langkah akumulasi — bukan di akhir.
 *
 * Gunakan properti:
 *   (a + b) % m = ((a % m) + (b % m)) % m
 *   (a × b) % m = ((a % m) × (b % m)) % m
 *
 * Input format  : Baris 1: N dan M
 *                 Baris 2: N bilangan bulat A[i]
 * Output format : Dua baris — sum mod M, lalu product mod M
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 2 ≤ M ≤ 10^9
 *                 0 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:            Sample Output 1:
 * 5 1000000007               15
 * 1 2 3 4 5                  120
 *
 * Sample Input 2:            Sample Output 2:
 * 3 7                        4
 * 10 20 30                   1
 *
 * Sample Input 3:            Sample Output 3:
 * 4 100                      7
 * 1000000000 999999999 5 3   0
 *
 * NOTE Sample 2: sum = 60 → 60 % 7 = 4 (60 = 8×7 + 4).
 *                product = 6000 → 6000 % 7 = 1 (6000 = 857×7 + 1).
 * NOTE Sample 3: sum = 2000000007 → % 100 = 7.
 *                product mengandung 10^9 yang habis dibagi 100 → hasil 0.
 *
 * HINT: Perhatikan A[i] bisa 10^9 dan M bisa 10^9. Perkalian dua nilai
 *       sebesar itu = 10^18 → masih muat long long, tapi TIDAK muat int.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int sum = 0;
    int fact = 1;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        sum = (sum + x) % m;
        fact = (fact * x) % m;
    }

    cout << sum << endl;
    cout << fact;
}