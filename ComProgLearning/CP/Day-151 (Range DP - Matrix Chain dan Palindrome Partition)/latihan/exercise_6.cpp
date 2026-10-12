/*
============================================================
🏋️ Exercise 6: Memotong Batang Bambu (Minimum Cost to Cut a Stick)
============================================================
Day: 151 | Difficulty: Hard | Topic: Range DP on Coordinates
Source: LeetCode 1547 / Classic DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki sebuah batang bambu dengan panjang awal L meter, membentang dari titik 0 hingga L.
Terdapat C titik pemotongan yang harus dilakukan, yaitu pada posisi cuts[0], cuts[1], ..., cuts[C-1].
Urutan pemotongan bebas kamu tentukan sendiri.

Setiap kali kamu memotong sebuah segmen bambu, biaya yang harus kamu bayar adalah
SEBESAR PANJANG SEGMEN BAMBU yang sedang dipotong saat itu.
Setelah dipotong, segmen tersebut terbagi dua, dan pemotongan berikutnya hanya membayar
panjang dari sub-segmen bambu yang relevan.

Tentukan BIAYA TOTAL MINIMUM yang diperlukan untuk menyelesaikan seluruh C titik pemotongan.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat L dan C.
- Baris kedua berisi C bilangan bulat cuts[0], cuts[1], ..., cuts[C-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: biaya total pemotongan minimum.

📏 CONSTRAINTS:
- 2 <= L <= 1.000.000
- 1 <= C <= 100
- 1 <= cuts[i] < L
- Semua nilai dalam cuts saling berbeda.

📎 SAMPLE INPUT 1:
7 4
1 3 4 5

📎 SAMPLE OUTPUT 1:
16

[Penjelasan Sample 1:
Urutan pemotongan optimal:
1. Potong pada posisi 3: biaya = 7 (panjang segmen [0, 7]). Segmen terbelah menjadi [0, 3] dan [3, 7].
2. Potong pada posisi 4 di segmen [3, 7]: biaya = 7 - 3 = 4. Terbelah menjadi [3, 4] dan [4, 7].
3. Potong pada posisi 5 di segmen [4, 7]: biaya = 7 - 4 = 3.
4. Potong pada posisi 1 di segmen [0, 3]: biaya = 3 - 0 = 3.
Total biaya = 7 + 4 + 3 + 3 = 16.]

📎 SAMPLE INPUT 2:
9 5
5 6 1 4 2

📎 SAMPLE OUTPUT 2:
22

💡 HINT:
- Masukkan batas ujung 0 dan L ke dalam array titik potong:
  titik = [0, cuts[0], ..., cuts[C-1], L], lalu URUTKAN secara menaik.
- Sekarang masalah berubah menjadi Range DP pada indeks titik potong:
  dp[l][r] = biaya minimum memotong semua titik potong di antara indeks l dan r.
- Panjang segmen yang dipotong adalah: `titik[r] - titik[l]`.
- Transisi:
  dp[l][r] = min_{l < k < r} (dp[l][k] + dp[k][r]) + (titik[r] - titik[l]).
- Basis: dp[l][l + 1] = 0 (tidak ada titik potong di antara l dan l + 1).
- Loop luar: panjang rentang `len` dari 2 sampai m - 1 (di mana m adalah ukuran array titik).

🎯 Learning Goals:
- [ ] Memetakan koordinat kontinu ke dalam indeks diskret untuk Range DP.
- [ ] Memahami hubungan pemotongan dengan pengelompokan sub-segmen.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, c;
    if (!(cin >> L >> c)) return 0;

    vector<int> cuts(c);
    for (int i = 0; i < c; i++) {
        cin >> cuts[i];
    }

    // TODO: Selesaikan Minimum Cost to Cut a Stick
    // 1. Tambahkan 0 dan L, urutkan array cuts
    // 2. Tabulasi dp[l][r]
    // 3. Cetak dp[0][m - 1]

    return 0;
}
