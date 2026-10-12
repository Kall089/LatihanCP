/*
============================================================
🏋️ Exercise 1: Konvoi Logistik Festival (Sum Squared Partition D&C DP)
============================================================
Day: 267 | Difficulty: Medium | Topic: Divide & Conquer DP Optimization
Source: Classic D&C DP Optimization
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah festival logistik mengatur N buah peti barang yang berjejer rapi dalam satu barisan.
Peti ke-i memiliki bobot a[i]. Urutan peti tidak boleh diubah.
Kamu harus membagi seluruh barisan N peti tersebut menjadi TEPAT K rombongan (segmen) berurutan tak kosong.
Biaya pengiriman satu rombongan dari peti ke-l sampai peti ke-r adalah KUADRAT DARI TOTAL BOBOTNYA:
`Cost(l, r) = (sum_{p=l}^r a[p])^2`.

Tentukan TOTAL BIAYA PENGIRIMAN MINIMUM untuk membagi N peti menjadi tepat K rombongan!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION agar lolos batas waktu O(K * N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum.

📏 CONSTRAINTS:
- 1 <= K <= min(N, 30)
- 1 <= N <= 20.000
- 0 <= a[i] <= 1.000.000
- Total jumlah seluruh a[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4 2
4 1 2 3

📎 SAMPLE OUTPUT 1:
50

[Penjelasan Sample 1:
Bagi menjadi 2 rombongan:
Rombongan 1: [4, 1] -> total bobot = 5, biaya = 5^2 = 25.
Rombongan 2: [2, 3] -> total bobot = 5, biaya = 5^2 = 25.
Total biaya = 25 + 25 = 50.]

📎 SAMPLE INPUT 2:
1 1
7

📎 SAMPLE OUTPUT 2:
49

[Penjelasan Sample 2:
Hanya ada 1 peti dan 1 rombongan: biaya = 7^2 = 49.]

📎 SAMPLE INPUT 3:
3 3
0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Gunakan rekurensi:
  `dp[g][i] = min_{g-1 <= j < i} { dp[g-1][j] + (pref[i] - pref[j])^2 }`.
- Fungsi biaya kuadrat penjumlahan memenuhi Quadrangle Inequality (Sifat Monge),
  sehingga titik potong optimal `opt[g][i]` bersifat monoton tidak menurun.
- Gunakan fungsi rekursif `solve(l, r, opt_l, opt_r)` untuk menghitung tiap layer `g`.

🎯 Learning Goals:
- [ ] Memahami implementasi dasar Divide and Conquer DP Optimization.
- [ ] Memanfaatkan Prefix Sum untuk menghitung biaya segmen dalam O(1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Divide & Conquer DP Optimization

    return 0;
}
