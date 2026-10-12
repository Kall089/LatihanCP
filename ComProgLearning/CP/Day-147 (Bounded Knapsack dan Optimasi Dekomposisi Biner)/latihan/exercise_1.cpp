/*
============================================================
🏋️ Exercise 1: Paket Logistik Pulau (Bounded Knapsack Klasik)
============================================================
Day: 147 | Difficulty: Easy | Topic: Bounded Knapsack Dasar
Source: Classic Bounded Knapsack / HDU 2191
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perahu logistik dengan kapasitas bobot maksimum W akan membawa bantuan
ke pulau terpencil. Terdapat N jenis barang bantuan.
Satu unit barang jenis ke-i memiliki bobot w[i], nilai manfaat v[i], dan persediaan
stok terbatas sebanyak c[i] unit.
Kamu boleh memilih 0, 1, 2, ..., hingga paling banyak c[i] unit untuk setiap jenis barang.
Tentukan total manfaat maksimum yang dapat dibawa oleh perahu tanpa melebihi kapasitas W.
Perahu boleh menyisakan ruang kapasitas kosong.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya, masing-masing berisi tiga bilangan bulat: w[i], v[i], dan c[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: nilai manfaat maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 60
- 0 <= W <= 20.000
- 1 <= w[i] <= 20.000
- 0 <= v[i] <= 10^9
- 0 <= c[i] <= 10^9

📎 SAMPLE INPUT 1:
2 10
2 3 5
3 5 1

📎 SAMPLE OUTPUT 1:
15

[Penjelasan Sample 1:
Ambil 5 unit barang ke-1: total bobot = 5 * 2 = 10 <= 10, total manfaat = 5 * 3 = 15.
Lebih menguntungkan daripada mengambil barang ke-2 (bobot 3 manfaat 5) + 3 unit barang 1 (bobot 6 manfaat 9) = 14.]

📎 SAMPLE INPUT 2:
1 10
2 3 2

📎 SAMPLE OUTPUT 2:
6

[Penjelasan Sample 2:
Hanya tersedia 2 unit barang ke-1: total bobot 2*2=4 <= 10, manfaat = 2*3 = 6.]

📎 SAMPLE INPUT 3:
1 0
1 8 10

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3: Kapasitas perahu 0, tidak bisa membawa barang apa pun]

💡 HINT:
- Batasi stok efektif c_eff = min(c[i], W / w[i]).
- Pecah c_eff menjadi paket-paket biner: k = 1, 2, 4, 8, ... dan sisa.
- Setiap paket virtual berbobot k * w[i] dan bernilai k * v[i].
- Jalankan 0/1 Knapsack dengan LOOP MUNDUR dari W ke bobot_paket.

🎯 Learning Goals:
- [ ] Mampu menerapkan Dekomposisi Biner pada Bounded Knapsack.
- [ ] Memahami perlunya loop kapasitas mundur untuk setiap paket biner.
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
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan dengan Bounded Knapsack Dekomposisi Biner
    // 1. Inisialisasi vector<ll> dp(W + 1, 0)
    // 2. Untuk setiap barang i:
    //    Batasi stok: c_eff = min(c[i], (ll)(W / w[i]))
    //    Pecah c_eff secara biner menjadi paket-paket
    //    Update dp secara mundur dari W ke bobot_paket
    // 3. Cetak dp[W]

    return 0;
}
