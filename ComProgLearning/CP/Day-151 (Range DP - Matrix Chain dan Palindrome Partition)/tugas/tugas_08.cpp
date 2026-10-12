/*
============================================================
📋 TUGAS 08: Permainan Angka Mengambil Ujung (Game Theory DP)
============================================================
Source: LeetCode 486 (Predict the Winner) / AtCoder DP Contest L (Deque)
Difficulty: Medium-Hard
Topics: Range DP Minimax, Two-Player Game

PROBLEM:
Alice dan Bob memainkan sebuah permainan dengan array berisi N bilangan bulat a[0], ..., a[N-1].
Pemain bergantian mengambil giliran, dimulai dari Alice.
Pada setiap giliran, seorang pemain hanya boleh mengambil sebuah angka dari ujung kiri PALING LUAR
atau ujung kanan PALING LUAR dari array yang tersisa saat itu, lalu angka tersebut dihapus dari array.
Skor akhir setiap pemain adalah jumlah total angka yang ia kumpulkan.
Kedua pemain bermain secara optimal: Alice ingin memaksimumkan (Skor Alice - Skor Bob),
sedangkan Bob ingin meminimalkan selisih tersebut.

Tentukan nilai akhir dari (Skor Alice - Skor Bob) jika kedua pemain bermain optimal.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: selisih (Skor Alice - Skor Bob).

CONSTRAINTS:
1 <= N <= 1.000
-10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
3
1 5 2

SAMPLE OUTPUT 1:
-2
(Penjelasan: Alice ambil 1 (tersisa [5, 2]). Bob pasti ambil 5 (tersisa [2]). Alice ambil 2.
Skor Alice = 1 + 2 = 3, Skor Bob = 5. Selisih = 3 - 5 = -2.
Jika Alice ambil 2 (tersisa [1, 5]), Bob ambil 5 (tersisa [1]), Alice ambil 1. Skor Alice = 3, Bob = 5. Selisih tetap -2)

SAMPLE INPUT 2:
4
1 5 233 7

SAMPLE OUTPUT 2:
222
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Selesaikan Permainan Deque dengan Range DP
    // dp[l][r] = keuntungan bersih maksimum pemain yang sedang giliran pada rentang a[l..r]
    // dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1])
    // Basis: dp[i][i] = a[i]

    return 0;
}
