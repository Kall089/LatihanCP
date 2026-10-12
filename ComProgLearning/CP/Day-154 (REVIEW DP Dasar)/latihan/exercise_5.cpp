/*
============================================================
🏋️ Exercise 5: Pemotongan Bambu Biaya Minimum (Interval / Range DP)
============================================================
Day: 154 | Difficulty: Hard | Topic: Interval DP / Stick Cutting
Source: LeetCode 1547 (Minimum Cost to Cut a Stick) / Review Synthesis
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki sebatang bambu lurus dengan panjang L meter. Batang bambu ini diberi tanda
koordinat dari 0 hingga L.
Terdapat M titik pada bambu yang harus dipotong, yang koordinatnya diberikan dalam array `cuts`.
Setiap kali kamu memotong sebuah segmen bambu, BIAYA yang harus dibayar adalah sama dengan
PANJANG SEGMEN BAMBU TERSEBUT sebelum dipotong.

Sebagai contoh: jika kamu memiliki bambu sepanjang 7 meter (dari koordinat 0 ke 7) dan memotong
di koordinat 3, kamu membayar biaya 7. Sekarang bambu terbagi menjadi dua segmen: [0, 3] dan [3, 7].
Jika selanjutnya kamu memotong segmen [0, 3] di koordinat 1, biayanya adalah 3.
Total biaya = 7 + 3 = 10.

Kamu bebas menentukan URUTAN pemotongan.
Tentukan BIAYA MINIMUM untuk menyelesaikan seluruh M pemotongan!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat L dan M.
- Baris kedua berisi M bilangan bulat positif menyatakan posisi titik potong.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: biaya minimum yang diperlukan.

📏 CONSTRAINTS:
- 2 <= L <= 1.000.000
- 1 <= M <= 100
- 1 <= cuts[i] < L
- Semua elemen cuts unik

📎 SAMPLE INPUT 1:
7 4
1 3 4 5

📎 SAMPLE OUTPUT 1:
16

[Penjelasan Sample 1:
Urutan potong optimal:
1. Potong di 3: biaya 7. Batang terbagi [0, 3] dan [3, 7].
2. Potong [0, 3] di 1: biaya 3. Batang terbagi [0, 1] dan [1, 3].
3. Potong [3, 7] di 4: biaya 4. Batang terbagi [3, 4] dan [4, 7].
4. Potong [4, 7] di 5: biaya 2.
Total biaya = 7 + 3 + 4 + 2 = 16.]

📎 SAMPLE INPUT 2:
9 5
5 6 1 4 2

📎 SAMPLE OUTPUT 2:
22

💡 HINT:
- Urutkan array titik potong, lalu tambahkan titik ujung: `0` di awal dan `L` di akhir.
  Sekarang kita memiliki array `A` berukuran `M + 2`: `A = [0, cuts[0], ..., cuts[M-1], L]`.
- Definisikan state:
  `dp[i][j]` = biaya minimum untuk memotong seluruh titik potong di antara indeks i dan j
  (yaitu dari koordinat A[i] sampai A[j]).
- Base case: jika `j == i + 1` (tidak ada titik potong di antara A[i] dan A[j]), `dp[i][j] = 0`.
- Transisi:
  Untuk setiap titik potong `k` di antara i dan j (`i < k < j`):
  `dp[i][j] = min_{i < k < j} (dp[i][k] + dp[k][j]) + (A[j] - A[i])`.
- Urutan loop: WAJIB loop atas panjang rentang `len = 2` sampai `M + 1`!

🎯 Learning Goals:
- [ ] Menguasai pola Interval / Range DP dengan reduksi titik batas.
- [ ] Memahami struktur loop interval: dari rentang terpendek menuju rentang penuh.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll L;
    int m;
    if (!(cin >> L >> m)) return 0;

    // TODO: Selesaikan Interval Stick Cutting DP

    return 0;
}
