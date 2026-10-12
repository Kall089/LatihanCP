/*
============================================================
📋 TUGAS 02: Paket Tiket Wahana Bermain
============================================================
Source: Competitive Programming Classic
Difficulty: Easy
Topics: Unbounded Knapsack (At Least K Target)

PROBLEM:
Taman bermain menjual N jenis paket tiket.
Paket ke-i memberikan b[i] lembar tiket dan berharga c[i] rupiah.
Setiap jenis paket boleh dibeli berkali-kali tanpa batas.
Kamu membutuhkan SETIDAKNYA X lembar tiket untuk bermain semua wahana.
(Boleh mendapatkan lebih dari X tiket jika total biayanya lebih murah).
Tentukan biaya minimum yang harus dikeluarkan.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
N baris berikutnya, masing-masing berisi dua bilangan bulat b[i] dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: biaya minimum untuk mendapatkan setidaknya X tiket.

CONSTRAINTS:
1 <= N <= 100
1 <= X <= 10.000
1 <= b[i] <= 10.000
1 <= c[i] <= 10.000

SAMPLE INPUT 1:
2 5
3 4
2 3

SAMPLE OUTPUT 1:
7
(Penjelasan: Beli 1 paket 3 tiket (biaya 4) + 1 paket 2 tiket (biaya 3) = total 5 tiket, biaya 7)

SAMPLE INPUT 2:
2 5
3 10
10 15

SAMPLE OUTPUT 2:
15
(Penjelasan: Beli 1 paket 10 tiket seharga 15 lebih murah dari dua paket 3 tiket seharga 20)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> b(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i] >> c[i];
    }

    // TODO: Selesaikan dengan DP Unbounded Knapsack
    // Catatan: Target adalah >= x. Ukuran array bisa dibuat hingga x + max(b)
    // atau di-clamp pada x: dp[min(x, i + b[k])] = min(...)

    return 0;
}
