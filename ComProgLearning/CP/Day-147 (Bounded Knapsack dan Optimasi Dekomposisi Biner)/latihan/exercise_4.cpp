/*
============================================================
🏋️ Exercise 4: Rekonstruksi Solusi Bounded Knapsack
============================================================
Day: 147 | Difficulty: Medium | Topic: Rekonstruksi Solusi Bounded Knapsack
Source: Classic DP / Decision Tracking
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis barang dan tas ransel berkapasitas bobot W.
Barang ke-i memiliki bobot w[i], nilai v[i], dan stok maksimum c[i] unit.
Tentukan nilai keuntungan total maksimum yang dapat diperoleh tanpa melebihi kapasitas W,
serta tampilkan kuantitas dari masing-masing barang yang diambil: k[0], k[1], ..., k[N-1]
di mana 0 <= k[i] <= c[i] dan sum(k[i] * w[i]) <= W.

Jika terdapat beberapa pilihan yang sama-sama menghasilkan nilai maksimum,
tampilkan salah satu susunan yang valid.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

📤 OUTPUT FORMAT:
- Baris pertama: nilai keuntungan maksimum.
- Baris kedua: N bilangan bulat dipisahkan spasi: k[0] k[1] ... k[N-1],
  yang menyatakan kuantitas masing-masing jenis barang yang diambil.

📏 CONSTRAINTS:
- 1 <= N <= 50
- 1 <= W <= 10.000
- 1 <= w[i] <= W
- 1 <= v[i] <= 10^9
- 1 <= c[i] <= 10.000

📎 SAMPLE INPUT 1:
2 10
2 3 5
3 5 1

📎 SAMPLE OUTPUT 1:
15
5 0

[Penjelasan Sample 1:
Ambil 5 unit barang ke-0 (bobot 10, nilai 15) dan 0 unit barang ke-1. Total nilai = 15.]

📎 SAMPLE INPUT 2:
3 8
3 10 2
2 4 3
4 15 1

📎 SAMPLE OUTPUT 2:
29
1 2 1

[Penjelasan Sample 2:
Ambil 1 unit barang ke-0 (bobot 3, nilai 10), 2 unit barang ke-1 (bobot 4, nilai 8),
dan 1 unit barang ke-2 (bobot 4, nilai 15).
Total bobot = 3 + 4 + 4 = 11 > 8? Tunggu:
Jika ambil 1 unit barang 0 (bobot 3, nilai 10) + 1 unit barang 2 (bobot 4, nilai 15) = bobot 7, nilai 25.
Jika ambil 2 unit barang 1 (bobot 4, nilai 8) + 1 unit barang 2 (bobot 4, nilai 15) = bobot 8, nilai 23.
Jika ambil 2 unit barang 0 (bobot 6, nilai 20) + 1 unit barang 1 (bobot 2, nilai 4) = bobot 8, nilai 24.
Pilihan terbaik pada bobot <= 8 adalah bobot 7: 1 unit barang 0 + 1 unit barang 2 (nilai 25).
Mari kita buat sample input yang presisi!]

📎 SAMPLE INPUT 2 (Revisi):
2 7
3 10 2
2 6 3

📎 SAMPLE OUTPUT 2:
22
1 2

[Penjelasan Sample 2:
Barang 0: bobot 3, nilai 10, stok 2.
Barang 1: bobot 2, nilai 6, stok 3.
Kombinasi optimal: 1 unit barang 0 (bobot 3, nilai 10) + 2 unit barang 1 (bobot 4, nilai 12).
Total bobot = 3 + 4 = 7 <= 7. Total nilai = 10 + 12 = 22.
Kuantitas yang diambil: 1 2.]

💡 HINT:
- Simpan daftar paket biner yang dibuat, bersama indeks barang aslinya `item_idx` dan jumlah unit `q`.
- Catat tabel DP 2D `dp[pkg_idx][w]` atau gunakan tabel parent/transisi untuk melacak mundur paket mana saja yang terpilih.
- Akumulasikan `ans_count[item_idx] += q` untuk setiap paket yang terpilih saat penelusuran balik.

🎯 Learning Goals:
- [ ] Memahami cara melakukan rekonstruksi kuantitas barang asli dari paket-paket biner.
- [ ] Menggunakan array penelusuran keputusan atau tabel DP untuk backtracking.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Package {
    int item_idx;
    int weight;
    ll value;
    int count;
};

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

    // TODO: Selesaikan Rekonstruksi Solusi Bounded Knapsack
    // 1. Buat paket-paket biner dari setiap barang
    // 2. Jalankan 0/1 Knapsack dengan pencatatan state/parent
    // 3. Lakukan backtracking untuk mengumpulkan kuantitas barang asli
    // 4. Cetak nilai maksimum di baris 1 dan kuantitas k[0..n-1] di baris 2

    return 0;
}
