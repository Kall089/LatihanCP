/*
============================================================
🏋️ Exercise 3: Kurasi Paket Tepat Berat (Exact Knapsack Reconstruction)
============================================================
Day: 152 | Difficulty: Hard | Topic: Suffix 2D DP + Binary Decision String Reconstruction
Source: Educational / Knapsack Decision Tracking
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N barang berurutan, dinomori dari 1 hingga N.
Barang ke-i memiliki berat w[i] dan biaya pengadaan c[i].
Setiap barang hanya boleh dipilih paling banyak satu kali (0/1).
Kamu harus memilih sekumpulan barang sehingga total beratnya TEPAT bernilai W,
dengan TOTAL BIAYA PENGADAAN MINIMUM.

Representasikan keputusan pemilihan barang dalam bentuk string biner sepanjang N:
- Karakter ke-i bernilai '1' jika barang ke-i dipilih.
- Karakter ke-i bernilai '0' jika barang ke-i dilewati.

Aturan Pemecah Seri (Tie-Breaker):
Jika terdapat beberapa kombinasi barang yang menghasilkan biaya minimum yang sama,
pilih string keputusan yang TERKECIL SECARA LEKSIKOGRAFIS (di mana karakter '0' lebih kecil daripada '1').
Artinya, kita lebih memprioritaskan untuk MELEWATI ('0') barang-barang bernomor kecil sedapat mungkin!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan c[i] untuk barang ke-i.

📤 OUTPUT FORMAT:
- Jika tidak mungkin mencapai total berat tepat W, cetak `-1` saja.
- Jika mungkin:
  - Baris pertama: total biaya pengadaan minimum.
  - Baris kedua: string biner keputusan sepanjang N ('0' dan '1').

📏 CONSTRAINTS:
- 1 <= N <= 200
- 0 <= W <= 3.000
- 1 <= w[i] <= 3.000
- 0 <= c[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 3
1 2
2 3
3 5

📎 SAMPLE OUTPUT 1:
5
001

[Penjelasan Sample 1:
Kombinasi yang berbobot tepat 3:
- Ambil barang 1 dan 2: berat 1 + 2 = 3, biaya 2 + 3 = 5, string "110".
- Ambil barang 3 saja: berat 3, biaya 5, string "001".
Biaya keduanya sama-sama 5 (minimum).
Secara leksikografis: "001" < "110" (karena pada karakter pertama, '0' < '1').
Maka string "001" yang dipilih.]

📎 SAMPLE INPUT 2:
2 0
1 0
2 0

📎 SAMPLE OUTPUT 2:
0
00

[Penjelasan Sample 2:
Target berat W = 0 tercapai tanpa mengambil barang mana pun, biaya 0, string "00".]

📎 SAMPLE INPUT 3:
1 3
2 5

📎 SAMPLE OUTPUT 3:
-1

[Penjelasan Sample 3:
Satu-satunya barang memiliki berat 2, mustahil mencapai target berat 3.]

💡 HINT:
- Gunakan Suffix 2D DP:
  `dp[i][s]` = biaya minimum untuk mengumpulkan sisa berat s menggunakan barang dari indeks i s.d. N-1.
- Basis: dp[N][0] = 0, dp[N][s] = INF untuk s > 0.
- Transisi mundur dari i = N-1 ke 0:
  dp[i][s] = min(dp[i+1][s], c[i] + dp[i+1][s - w[i]]).
- Rekonstruksi dari i = 0 ke N-1:
  Karena kita mengutamakan '0' daripada '1':
  Cek apakah `dp[i][s] == dp[i+1][s]`.
  Jika ya: ambil keputusan '0' (skip barang i).
  Jika tidak: ambil keputusan '1' (ambil barang i), lalu `s -= w[i]`.

🎯 Learning Goals:
- [ ] Menerapkan Suffix 2D DP untuk menghasilkan bitstring keputusan leksikografis optimal.
- [ ] Memahami penanganan target berat eksak (exact weight) dengan inisialisasi tak terhingga (INF).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // TODO: Selesaikan Suffix 2D DP Exact Knapsack
    // 1. Inisialisasi dp[n+1][W+1] dengan INF, dp[n][0] = 0
    // 2. Tabulasi dari i = n - 1 ke 0
    // 3. Rekonstruksi string dari i = 0 ke n - 1

    return 0;
}
