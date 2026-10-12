/*
============================================================
📋 TUGAS 02: Tukar Uang Kertas di Bank
============================================================
Source: Classic Bounded Coin Change
Difficulty: Easy-Medium
Topics: Bounded Coin Change Min, Sentinel INF

PROBLEM:
Kamu ingin menukarkan sejumlah uang tunai tepat sebesar X rupiah di teller bank.
Bank memiliki N jenis pecahan uang kertas. Pecahan uang ke-i bernilai w[i] rupiah
dan teller hanya memiliki stok terbatas sebanyak c[i] lembar.
Tentukan jumlah lembar uang kertas MINIMUM yang dapat diberikan teller untuk
membentuk nominal tepat X rupiah.
Jika tidak ada kombinasi pecahan yang menghasilkan tepat nominal X, keluarkan -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: jumlah lembar uang kertas minimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 100
1 <= X <= 20.000
1 <= w[i] <= X
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
3 11
5 2
2 4
1 5

SAMPLE OUTPUT 1:
3
(Penjelasan: Ambil dua lembar 5 (nominal 10) + satu lembar 1 (nominal 1) = 3 lembar. Total nominal 11)

SAMPLE INPUT 2:
2 10
4 2
3 1

SAMPLE OUTPUT 2:
-1
(Penjelasan: Kombinasi pecahan 4 dan 3 tidak dapat membentuk nominal tepat 10 dengan stok yang ada)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> w(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Coin Change Min
    // Inisialisasi vector<int> dp(x + 1, INF); dp[0] = 0;
    // Pecah c[i] secara biner q
    // dp[s] = min(dp[s], dp[s - q * w[i]] + q)

    return 0;
}
