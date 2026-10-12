/*
============================================================
📋 TUGAS 07: Jual Beli K Komoditas Emas dengan Jeda Transaksi
============================================================
Source: Gold Trading with 1-Day Cooldown
Difficulty: Hard
Topics: Aliens Trick, State Machine DP

PROBLEM:
Diberikan riwayat harga emas P[0], ..., P[N-1] selama N hari.
Kamu boleh melakukan paling banyak K transaksi jual-beli.
Setelah menjual emas di hari j, kamu harus menunggu setidaknya 1 hari istirahat (cooldown),
artinya pembelian berikutnya baru boleh dilakukan paling cepat pada hari j + 2.
Maksimumkan total keuntungan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif P[0], ..., P[N-1].

OUTPUT FORMAT:
Satu baris berisi keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= K <= N
0 <= P[i] <= 1.000.000.000

SAMPLE INPUT 1:
5 2
1 2 3 0 2

SAMPLE OUTPUT 1:
3
(Beli hari 0 (harga 1), jual hari 2 (harga 3) -> untung 2.
 Hari 3 jeda cooldown. Beli hari 3? Tunggu: jual hari 2 -> cooldown hari 3 -> beli hari 4?
 Di sample: beli hari 0 jual hari 1 (untung 1) -> cooldown hari 2 -> beli hari 3 jual hari 4 (untung 2) -> total = 3!)

SAMPLE INPUT 2:
1 1
10

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + Cooldown State DP

    return 0;
}
