/*
============================================================
🏋️ Exercise 2: Kasir dengan Laci Terbatas (Bounded Coin Change Min)
============================================================
Day: 147 | Difficulty: Medium | Topic: Bounded Coin Change Min
Source: Competitive Programming Classic
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang kasir harus memberikan kembalian tepat sebesar nominal X rupiah.
Terdapat N jenis pecahan koin di laci kasir. Pecahan ke-i bernilai w[i] rupiah
dan hanya tersedia paling banyak c[i] keping.
Tentukan jumlah keping koin minimum yang diperlukan untuk membentuk tepat nominal X.
Jika tidak mungkin membentuk tepat nominal X dengan stok koin yang ada, keluarkan -1.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: jumlah keping koin minimum, atau -1 jika mustahil.

📏 CONSTRAINTS:
- 1 <= N <= 60
- 0 <= X <= 20.000
- 1 <= w[i] <= 20.000
- 0 <= c[i] <= 10^9

📎 SAMPLE INPUT 1:
2 6
3 2
1 6

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Gunakan dua koin bernilai 3: 3 + 3 = 6 (2 keping koin).
Stok koin 3 ada 2 keping, mencukupi.]

📎 SAMPLE INPUT 2:
1 6
3 1

📎 SAMPLE OUTPUT 2:
-1

[Penjelasan Sample 2:
Koin 3 hanya ada 1 keping, tidak cukup membentuk 6.]

📎 SAMPLE INPUT 3:
1 0
9 0

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3: Nominal 0 membutuhkan 0 keping koin]

💡 HINT:
- Inisialisasi array DP berukuran (X + 1) dengan nilai INF (misal 1e9).
- Base case: dp[0] = 0.
- Pecah stok c[i] menjadi paket biner q.
- Paket q keping berbobot q * w[i] dan MENAMBAH BIAYA SEBANYAK q KEPING (bukan 1 keping!).
- Loop kapasitas mundur dari X ke q * w[i]:
  if (dp[s - q * w[i]] != INF) dp[s] = min(dp[s], dp[s - q * w[i]] + q).

🎯 Learning Goals:
- [ ] Menerapkan Dekomposisi Biner pada masalah Minimasi Koin dengan stok terbatas.
- [ ] Memahami bahwa bobot biaya dari paket berukuran q adalah q keping koin.
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
    vector<long long> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Coin Change Minimum
    // 1. vector<int> dp(x + 1, INF), dp[0] = 0
    // 2. Dekomposisi biner untuk setiap koin
    // 3. Update mundur: dp[s] = min(dp[s], dp[s - q * w[i]] + q)
    // 4. Cetak dp[x] jika dp[x] != INF, atau -1 jika INF

    return 0;
}
