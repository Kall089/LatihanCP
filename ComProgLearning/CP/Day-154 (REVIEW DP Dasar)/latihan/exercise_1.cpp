/*
============================================================
🏋️ Exercise 1: Agenda Stan dan Anggaran (House Robber + Knapsack)
============================================================
Day: 154 | Difficulty: Easy-Medium | Topic: Hybrid 2D DP (State Synthesis)
Source: Review Synthesis / DP Kombinasi
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N stan pameran festival yang berjejer dalam satu garis lurus (dinomori 1 sampai N).
Mengunjungi stan ke-i membutuhkan biaya anggaran sebesar w[i] dan memberikan kepuasan sebesar v[i].
Kamu memiliki total anggaran maksimal sebesar W.

Aturan festival:
1. Total biaya semua stan yang kamu pilih TIDAK BOLEH melebihi anggaran W.
2. Karena aturan kerumunan, kamu TIDAK BOLEH memilih dua stan yang bersebelahan langsung
   (jika stan i dipilih, maka stan i-1 dan stan i+1 tidak boleh dipilih).
3. Kamu diperbolehkan tidak memilih stan mana pun (kepuasan 0).

Tentukan KEPUASAN MAKSIMUM yang dapat kamu peroleh dengan mematuhi kedua batasan tersebut!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: kepuasan maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 200
- 0 <= W <= 5.000
- 1 <= w[i] <= 5.000
- 0 <= v[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 4
2 5
2 100
2 5

📎 SAMPLE OUTPUT 1:
100

[Penjelasan Sample 1:
Stan 2 memberi kepuasan 100 dengan biaya 2 <= 4.
Jika memilih stan 1 dan stan 3, kepuasan hanya 5 + 5 = 10.
Maka pilihan terbaik adalah memilih stan 2 saja dengan kepuasan 100.]

📎 SAMPLE INPUT 2:
1 0
1 9

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Anggaran W = 0, sedangkan stan 1 butuh biaya 1. Tidak ada stan yang bisa dipilih. Kepuasan 0.]

📎 SAMPLE INPUT 3:
3 4
2 6
2 7
2 6

📎 SAMPLE OUTPUT 3:
12

[Penjelasan Sample 3:
Stan 1 (biaya 2, nilai 6) dan Stan 3 (biaya 2, nilai 6) tidak bersebelahan.
Total biaya = 2 + 2 = 4 <= 4. Total kepuasan = 6 + 6 = 12.
Memilih stan 2 saja hanya memberi 7.]

💡 HINT:
- Masalah ini menggabungkan House Robber (tidak boleh bersebelahan) dan Knapsack (anggaran W).
- Definisikan state:
  `dp[i][s]` = kepuasan maksimum mempertimbangkan i stan pertama dengan anggaran tersisa s.
- Di setiap stan i, ada 2 opsi:
  1. Lewatkan stan i: `dp[i][s] = dp[i - 1][s]`.
  2. Ambil stan i (jika s >= w[i]): karena tidak boleh bersebelahan, stan i-1 TIDAK boleh diambil.
     Artinya, state sebelumnya harus ditarik dari `dp[i - 2][s - w[i]] + v[i]`.
- Maka: `dp[i][s] = max(dp[i - 1][s], dp[i - 2][s - w[i]] + v[i])`.
- Gunakan 3 baris buffer (`older`, `prev`, `cur`) atau tabel 2D ukuran (N + 1) x (W + 1).

🎯 Learning Goals:
- [ ] Menganalisis dan menggabungkan dua pola DP klasik menjadi satu formulasi state terpadu.
- [ ] Memahami dependensi langkah i - 2 pada variasi House Robber dengan kapasitas.
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

    // TODO: Selesaikan hybrid House Robber + Knapsack

    return 0;
}
