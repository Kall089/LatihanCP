/*
============================================================
📋 TUGAS 05: Belanja Hemat Bounded (Minimasi Biaya Target Minimal)
============================================================
Source: Competitive Programming Classic
Difficulty: Medium
Topics: Bounded Knapsack Min Cost, At-Least Target

PROBLEM:
Kamu perlu mengumpulkan poin loyalitas MINIMAL sebanyak P poin dari sebuah supermarket.
Supermarket menawarkan N jenis paket belanja promo.
Paket promo ke-i memberikan w[i] poin loyalitas, berharga cost[i] rupiah,
dan setiap pelanggan hanya diperbolehkan membeli paling banyak c[i] paket promo tersebut.
Tentukan pengeluaran biaya MINIMUM yang diperlukan untuk memperoleh poin loyalitas
SEDIKITNYA P poin (boleh lebih dari P jika lebih murah).

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan P.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], cost[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: biaya minimum untuk mengumpulkan >= P poin.

CONSTRAINTS:
1 <= N <= 100
1 <= P <= 10.000
1 <= w[i] <= 1.000
1 <= cost[i] <= 10^9
1 <= c[i] <= 500
Dijamin total poin dari semua paket yang tersedia >= P

SAMPLE INPUT 1:
2 10
4 15 2
3 10 3

SAMPLE OUTPUT 1:
35
(Penjelasan: Beli 1 paket promo 0 (4 poin, biaya 15) + 2 paket promo 1 (6 poin, biaya 20) = 10 poin, biaya 35)

SAMPLE INPUT 2:
1 5
7 20 2

SAMPLE OUTPUT 2:
20
(Penjelasan: Beli 1 paket promo langsung dapat 7 poin (>= 5), biaya 20)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p;
    if (!(cin >> n >> p)) return 0;

    vector<int> w(n);
    vector<ll> cost(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> cost[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Min Cost At-least Target
    // Batas atas poin maksimum yang perlu dicatat: p + max(w[i])
    // vector<ll> dp(max_target + 1, INF); dp[0] = 0;
    // Update mundur paket biner, lalu ambil min_{j >= p} dp[j]

    return 0;
}
