/*
============================================================
📋 TUGAS 08: Pembelian Snack dengan Kembalian Minimum
============================================================
Source: Competitive Programming Classic
Difficulty: Medium
Topics: Unbounded Knapsack (Upper Bound Exact Sum)

PROBLEM:
Mesin penjual otomatis (vending machine) tidak memiliki uang kembalian.
Sebuah snack berharga tepat X rupiah.
Kamu memiliki N pecahan koin berbeda c[0], ..., c[N-1] dalam jumlah tak terbatas.
Kamu harus membayar sejumlah uang Y >= X dengan kombinasi koinmu sedemikian
rupa sehingga nilai Y sekecil mungkin (uang lebih yang terbuang sekecil mungkin).
Tentukan nilai total pembayaran terkecil Y (Y >= X) yang bisa kamu bayarkan.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: nilai pembayaran terkecil Y >= X.

CONSTRAINTS:
1 <= N <= 50
1 <= X <= 100.000
1 <= c[i] <= 100.000

SAMPLE INPUT 1:
2 11
4 6

SAMPLE OUTPUT 1:
12
(Penjelasan: Kelipatan kombinasi 4 dan 6 yang >= 11 adalah 12 (4+4+4 atau 6+6))

SAMPLE INPUT 2:
3 10
3 5 7

SAMPLE OUTPUT 2:
10
(Penjelasan: Bisa membayar uang pas 5 + 5 = 10)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    int max_c = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        max_c = max(max_c, c[i]);
    }

    // TODO: Gunakan DP Boolean Unbounded Knapsack
    // Batas atas pencarian cukup sampai x + max_c.
    // Cari nilai y >= x pertama yang bernilai true pada tabel DP.

    return 0;
}
