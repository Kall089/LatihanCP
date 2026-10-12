/*
============================================================
🏋️ Exercise 6: Bounded Knapsack Kapasitas Tepat (Exact Target)
============================================================
Day: 147 | Difficulty: Hard | Topic: Exact Target Bounded Knapsack
Source: Classic DP / Exact Target Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki sebuah kontainer kargo yang harus diisi beban dengan bobot TOTAL
TEPAT SAMA DENGAN W (tidak boleh kurang satu gram pun dan tidak boleh lebih).
Terdapat N jenis barang muatan. Barang ke-i memiliki bobot w[i], nilai manfaat v[i],
dan jumlah persediaan stok sebanyak c[i] unit.
Kamu boleh mengambil 0, 1, ..., hingga paling banyak c[i] unit untuk barang ke-i.

Tentukan total nilai manfaat maksimum yang bisa diperoleh dengan total bobot tepat W.
Jika tidak ada kombinasi barang yang dapat menghasilkan total bobot tepat W, cetak -1.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: nilai manfaat maksimum dengan bobot tepat W, atau -1 jika mustahil.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 0 <= W <= 20.000
- 1 <= w[i] <= W
- 0 <= v[i] <= 10^9
- 0 <= c[i] <= 10^4

📎 SAMPLE INPUT 1:
2 7
3 5 2
2 4 3

📎 SAMPLE OUTPUT 1:
13

[Penjelasan Sample 1:
Ambil 1 unit barang 0 (bobot 3, nilai 5) dan 2 unit barang 1 (bobot 4, nilai 8).
Total bobot = 3 + 4 = 7 (tepat sama dengan W = 7).
Total nilai = 5 + 8 = 13.]

📎 SAMPLE INPUT 2:
1 5
2 10 100

📎 SAMPLE OUTPUT 2:
-1

[Penjelasan Sample 2:
Hanya ada barang berbobot 2. Kombinasi kelipatan 2 selalu genap, sehingga mustahil membentuk tepat bobot 5.]

📎 SAMPLE INPUT 3:
1 0
5 10 2

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Target bobot 0 tercapai dengan tidak mengambil barang apa pun, total nilai 0.]

💡 HINT:
- Inisialisasi `dp` berukuran W + 1 dengan sentinel -1 (menyatakan belum terjangkau).
- Base case: `dp[0] = 0`.
- Saat transisi knapsack loop mundur:
  hanya perbarui `dp[s]` jika kapasitas sebelumnya valid (`dp[s - pkg_weight] != -1`).
  `dp[s] = max(dp[s], dp[s - pkg_weight] + pkg_value)`.
- Cetak `dp[W]`.

🎯 Learning Goals:
- [ ] Memahami penanganan target tepat (Exact Target) menggunakan inisialisasi sentinel (-1).
- [ ] Mengombinasikan target tepat dengan Dekomposisi Biner pada Bounded Knapsack.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Exact Target Bounded Knapsack
    // 1. Inisialisasi vector<ll> dp(W + 1, -1); dp[0] = 0;
    // 2. Dekomposisi biner stok barang
    // 3. Update loop mundur dengan pengecekan dp[s - pkg_wt] != -1
    // 4. Cetak dp[W]

    return 0;
}
