/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_2.cpp
 * Topik : Modulo Bilangan Negatif (Normalisasi)
 * -----------------------------------------------
 * Diberikan Q query, masing-masing berisi dua bilangan bulat A dan M.
 * Untuk setiap query, cetak hasil A mod M dalam definisi MATEMATIS,
 * yaitu hasil selalu berada di rentang [0, M-1].
 *
 * Ingat: C++ memberi hasil NEGATIF untuk operand kiri negatif!
 *   (-7) % 3  di C++  = -1
 *   (-7) mod 3 matematis = 2
 *
 * Gunakan rumus normalisasi:
 *   ((a % m) + m) % m
 *
 * Mengapa bukan (a + m) % m? Karena a bisa jauh lebih negatif dari -m.
 * Ambil a % m dulu agar hasilnya masuk rentang (-m, m), baru +m.
 *
 * Input format  : Baris 1: Q
 *                 Q baris berikutnya: A dan M
 * Output format : Q baris, masing-masing hasil A mod M di [0, M-1]
 * Constraints   : 1 ≤ Q ≤ 100.000
 *                 -10^18 ≤ A ≤ 10^18
 *                 1 ≤ M ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 5                      2
 * -7 3                   4
 * -1 5                   1
 * 17 8                   0
 * -10 5                  3
 * -1000000000007 10
 *
 * Sample Input 2:        Sample Output 2:
 * 3                      0
 * 0 7                    6
 * -1 7                   1
 * 8 7
 *
 * HINT: A muat di long long, tapi A + M bisa mendekati batas jika tidak
 *       mengambil % lebih dulu. Urutan operasi itu penting.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    cin >> q;

    while (q--)
    {
        int a, m;
        cin >> a >> m;
    }
}