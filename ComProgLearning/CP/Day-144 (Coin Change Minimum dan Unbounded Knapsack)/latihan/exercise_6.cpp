/*
============================================================
🏋️ Exercise 6: Penukaran Koin dengan Biaya Transaksi
============================================================
Day: 144 | Difficulty: Hard | Topic: Weighted Unbounded Knapsack
Source: Competitive Programming Variation
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah bank menyediakan N jenis pecahan uang digital.
Pecahan ke-i memiliki nilai nominal c[i], namun setiap kali kamu menukarkan
pecahan tersebut, bank mengenakan biaya administrasi tetap sebesar p[i].
Setiap jenis pecahan tersedia dalam jumlah tak terbatas (boleh dipakai berkali-kali).

Kamu ingin membentuk nilai total tepat sebesar X dengan membayar total biaya
administrasi sesedikit mungkin.
Tentukan total biaya administrasi minimum yang harus dibayar.
Jika mustahil membentuk tepat nominal X dengan pecahan yang ada, cetak -1.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- N baris berikutnya, masing-masing berisi dua bilangan bulat c[i] dan p[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: biaya administrasi minimum, atau -1 jika mustahil.

📏 CONSTRAINTS:
- 1 <= N <= 200
- 1 <= X <= 100.000
- 1 <= c[i] <= 100.000
- 1 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
3 10
2 5
5 11
4 8

📎 SAMPLE OUTPUT 1:
21

[Penjelasan Sample 1:
Beberapa kombinasi untuk mencapai 10:
- Dua koin 5: biaya 11 + 11 = 22
- Lima koin 2: biaya 5 * 5 = 25
- Dua koin 4 + satu koin 2: biaya 8 + 8 + 5 = 21 (MINIMUM)]

📎 SAMPLE INPUT 2:
2 7
3 10
2 8

📎 SAMPLE OUTPUT 2:
26

[Penjelasan Sample 2:
Kombinasi pembentuk 7:
- Satu koin 3 + dua koin 2: biaya 10 + 8 + 8 = 26.]

📎 SAMPLE INPUT 3:
2 5
2 4
4 6

📎 SAMPLE OUTPUT 3:
-1

[Penjelasan Sample 3: Semua koin genap, tidak mungkin membentuk nominal 5 ganjil]

💡 HINT:
- Masalah ini analog dengan Unbounded Knapsack dengan tujuan mencari MINIMUM COST (biaya terkecil) untuk kapasitas TEPAT X.
- Gunakan tipe data long long untuk tabel DP dengan inisialisasi INF = 1e18.
- dp[0] = 0.
- Loop koin di luar atau nominal di dalam, pastikan arah loop maju i dari c[k] ke X.

🎯 Learning Goals:
- [ ] Menerapkan Unbounded Knapsack untuk optimasi minimum cost (bukan hanya koin count atau max value).
- [ ] Menangani exact target constraint dengan inisialisasi INF bertipe 64-bit.
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

    vector<int> c(n);
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> p[i];
    }

    // TODO: Selesaikan Weighted Unbounded Knapsack Minimum Cost
    // 1. vector<ll> dp(x + 1, INF)
    // 2. dp[0] = 0
    // 3. Loop setiap pecahan k
    // 4. Loop nominal i MAJU dari c[k] sampai x
    // 5. Jika dp[i - c[k]] != INF, dp[i] = min(dp[i], dp[i - c[k]] + p[k])
    // 6. Cetak dp[x] jika dp[x] != INF, atau -1 jika INF

    return 0;
}
