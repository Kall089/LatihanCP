/*
============================================================
🏋️ Exercise 3: Manifest Kapasitas Penuh (Exact Knapsack O(W) Space)
============================================================
Day: 153 | Difficulty: Hard | Topic: 1D Knapsack DP with Backward Loop
Source: Classic 0/1 Knapsack / Exact Weight
Time Limit: 2.0 detik | Memory Limit: 64 MB

📋 PROBLEM STATEMENT:
Sebuah kontainer kargo harus diisi hingga mencapai berat TEPAT W menggunakan sekumpulan barang
dari N barang yang tersedia.
Barang ke-i memiliki berat w[i] dan nilai ekonomi v[i].
Setiap barang boleh dimasukkan paling banyak satu kali (0/1).

Tentukan TOTAL NILAI MAKSIMUM yang dapat dikumpulkan sedemikian rupa sehingga total berat barang
yang masuk tepat sama dengan W.
Jika tidak ada kombinasi barang yang dapat menghasilkan berat tepat W, cetak `-1`.

Batasan: N hingga 500 dan W hingga 30.000.
Tabel 2D berukuran 501 x 30001 long long memakan sekitar ~120 MB (melebihi batas 64 MB).
Kamu DIHARUSKAN menggunakan satu array DP 1D berukuran O(W).

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total nilai maksimum yang tepat berbobot W, atau `-1` jika mustahil.

📏 CONSTRAINTS:
- 1 <= N <= 500
- 0 <= W <= 30.000
- 1 <= w[i] <= 30.000
- 0 <= v[i] <= 1.000.000.000
- Memori DP harus O(W).

📎 SAMPLE INPUT 1:
2 5
2 3
3 4

📎 SAMPLE OUTPUT 1:
7

[Penjelasan Sample 1:
Ambil barang 1 (berat 2, nilai 3) dan barang 2 (berat 3, nilai 4).
Total berat = 2 + 3 = 5 (tepat W), total nilai = 3 + 4 = 7.]

📎 SAMPLE INPUT 2:
1 4
2 3

📎 SAMPLE OUTPUT 2:
-1

[Penjelasan Sample 2:
Satu-satunya barang memiliki berat 2, tidak mungkin mencapai berat tepat 4.]

📎 SAMPLE INPUT 3:
1 0
1 99

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Kapasitas yang diminta W = 0, dapat dipenuhi tanpa mengambil barang mana pun, nilai 0.]

💡 HINT:
- Inisialisasi vector `dp` berukuran W + 1 dengan nilai sentinel `-1` (atau `-INF`).
- Base case: `dp[0] = 0` (berat 0 selalu dapat dicapai dengan nilai 0).
- Untuk setiap barang dengan berat `w` dan nilai `v`:
  - Lakukan loop kapasitas SECARA MUNDUR dari `s = W` turun ke `s = w`!
  - Mengapa mundur? Karena kita ingin `dp[s - w]` masih berisi hasil sebelum barang ini diproses,
    mencegah barang yang sama dipakai berulang kali.
  - `if (dp[s - w] != -1) dp[s] = max(dp[s], dp[s - w] + v);`
- Cetak `dp[W]`.

🎯 Learning Goals:
- [ ] Mereduksi dimensi Knapsack 0/1 dari O(N*W) menjadi O(W) menggunakan backward loop.
- [ ] Memahami penanganan target kapasitas eksak (exact weight) dengan inisialisasi unreachable.
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

    // TODO: Selesaikan Exact Knapsack dengan 1D DP O(W)
    // 1. Inisialisasi dp[0..W] dengan -1, dp[0] = 0
    // 2. Loop barang: baca w dan v langsung
    // 3. Loop kapasitas mundur dari W s.d. w

    return 0;
}
