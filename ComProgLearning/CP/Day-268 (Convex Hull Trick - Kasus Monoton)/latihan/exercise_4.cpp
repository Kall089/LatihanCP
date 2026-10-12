/*
============================================================
🏋️ Exercise 4: Akuisisi Lahan Persegi Panjang (Land Acquisition CHT)
============================================================
Day: 268 | Difficulty: Hard | Topic: Convex Hull Trick (Geometry Optimization)
Source: USACO Gold (Land Acquisition)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang tuan tanah ingin membeli N petak lahan yang berbentuk persegi panjang.
Petak lahan ke-i memiliki lebar w[i] dan panjang h[i].
Tuan tanah dapat mengelompokkan pembelian beberapa lahan sekaligus dalam satu transaksi.
Biaya pembelian satu kelompok lahan S didefinisikan sebagai:
`Biaya(S) = max_{k in S}(w[k]) * max_{k in S}(h[k])`.

Tuan tanah ingin membagi N lahan tersebut ke dalam satu atau lebih kelompok pembelian
sedemikian rupa sehingga TOTAL BIAYA PEMBELIAN SELURUH LAHAN ADALAH MINIMUM.

Selesaikan dengan CONVEX HULL TRICK DENGAN DEQUE setelah menyaring lahan terdominasi!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan h[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum akuisisi seluruh lahan.

📏 CONSTRAINTS:
- 1 <= N <= 100.000
- 1 <= w[i], h[i] <= 1.000.000

📎 SAMPLE INPUT 1:
4
100 1
15 15
20 5
1 100

📎 SAMPLE OUTPUT 1:
500

[Penjelasan Sample 1:
- Petak [20, 5] didominasi oleh [100, 1] dan [15, 15] (bisa digabung gratis).
- Kelompokkan [100, 1] dan [20, 5] (biaya max(100, 20) * max(1, 5) = 100 * 5 = 500?
  Atau kelompokkan [1, 100] sendirian (100) dan sisanya?
  Jika kelompok 1: [1, 100] (biaya 100), kelompok 2: [15, 15] dan [20, 5] dan [100, 1] (biaya 100 * 15 = 1500) -> 1600.
  Jika kelompok 1: [1, 100] dan [15, 15] -> biaya 15 * 100 = 1500.
  Jika kelompok 1: [1, 100] dan [15, 15] dan [20, 5] -> biaya 20 * 100 = 2000.
  Kelompokkan: [1, 100] (biaya 1*100=100) + [15, 15] + [100, 1]...
  Cara terbaik: Kelompok 1: {[1, 100]}, Kelompok 2: {[15, 15], [20, 5]}, Kelompok 3: {[100, 1]} -> 100 + 300 + 100 = 500.]

📎 SAMPLE INPUT 2:
2
10 10
5 5

📎 SAMPLE OUTPUT 2:
100
(Lahan [5, 5] didominasi oleh [10, 10], gabung jadi satu dengan biaya 10 * 10 = 100)

💡 HINT:
1. Urutkan lahan berdasarkan lebar w menaik (dan h menurun jika w sama).
2. Singkirkan lahan yang didominasi (lahan yang memiliki panjang h <= panjang lahan lain yang memiliki w >= dirinya).
3. Setelah disaring, lahan tersisa akan memiliki w menaik ketat dan h menurun ketat!
4. Bentuk DP interval:
   `dp[i] = min_{0 <= j < i} { dp[j] + h[j+1] * w[i] }`.
   Di mana slope `m = h[j+1]` menurun, dan query `x = w[i]` menaik!
5. Gunakan CHT Deque O(N).

🎯 Learning Goals:
- [ ] Menyaring data redundan/terdominasi menggunakan stack / sorting.
- [ ] Menghubungkan problem optimasi geometri 2D ke form CHT standar.
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

    // TODO: Saring lahan terdominasi lalu selesaikan dengan CHT Deque

    return 0;
}
