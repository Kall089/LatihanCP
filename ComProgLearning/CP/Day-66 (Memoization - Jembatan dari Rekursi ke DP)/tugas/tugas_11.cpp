/*
============================================================
📋 TUGAS 11: Permainan Memilih Kartu dari Kedua Ujung (Game DP Top-Down)
============================================================
Source: LeetCode 486 / Classic Game Theory DP
Difficulty: Medium
Topics: Top-Down Interval Memoization, Minimax

PROBLEM:
Diberikan barisan N buah kartu dengan nilai skor nums[0], ..., nums[N-1].
Dua pemain (Pemain 1 dan Pemain 2) bermain bergantian. Pemain 1 selalu bermain pertama.
Pada setiap giliran, seorang pemain dapat mengambil SATU KARTU dari ujung kiri atau ujung kanan barisan yang tersisa.
Kedua pemain bermain secara optimal untuk memaksimalkan selisih skor mereka terhadap lawan.

Hitung SELISIH SKOR MAKSIMUM yang dapat diperoleh Pemain 1 dibanding Pemain 2
(Skor Pemain 1 - Skor Pemain 2)!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI INTERVAL (Top-Down)!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat nums[0], ..., nums[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: selisih skor maksimum (bisa bernilai negatif jika pemain 1 kalah).

CONSTRAINTS:
1 <= N <= 1.000
-10.000 <= nums[i] <= 10.000

SAMPLE INPUT 1:
3
1 5 2

SAMPLE OUTPUT 1:
-2
(Pemain 1 ambil 1, Pemain 2 ambil 5, Pemain 1 ambil 2 -> Skor P1 = 3, Skor P2 = 5, Selisih = 3 - 5 = -2)

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

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    // TODO: Selesaikan dengan top-down interval memoization: solve(l, r)

    return 0;
}
