/*
============================================================
🏋️ Exercise 3: Bus Tambahan, Anggaran Tambahan (Flexible Groups D&C DP)
============================================================
Day: 267 | Difficulty: Hard | Topic: Divide & Conquer DP Optimization
Source: Classic D&C DP Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan transportasi mengangkut N kelompok penumpang yang memiliki beban muatan a[0], ..., a[N-1].
Operator diperbolehkan menyewa antara 1 hingga K bus (artinya jumlah bus g dapat dipilih bebas: 1 <= g <= K).
Setiap bus mendapatkan satu segmen penumpang berurutan tak kosong.
Biaya satu bus yang mengangkut segmen [l..r] adalah KUADRAT TOTAL BEBAN:
`Cost(l, r) = (sum_{p=l}^r a[p])^2`.

Selain itu, setiap bus yang disewa memerlukan BIAYA TETAP SEBESAR F per bus
(nilai F bisa negatif jika pemerintah memberikan subsidi per bus yang beroperasi).
Total biaya yang dibayarkan operator jika menggunakan g bus adalah:
`Total Biaya = (Jumlah biaya beban seluruh g bus) + g * F`.

Tentukan TOTAL BIAYA MINIMUM yang mungkin, serta JUMLAH BUS YANG DIGUNAKAN!
Jika terdapat lebih dari satu pilihan jumlah bus yang menghasilkan biaya minimum yang sama,
pilihlah JUMLAH BUS PALING SEDIKIT!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION!

📥 INPUT FORMAT:
- Baris pertama berisi tiga bilangan bulat N, K, dan F.
- Baris kedua berisi N bilangan bulat non-negatif a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi dua bilangan bulat dipisahkan spasi:
  [biaya minimum] [jumlah bus terpilih].

📏 CONSTRAINTS:
- 1 <= K <= min(N, 30)
- 1 <= N <= 20.000
- 0 <= a[i] <= 1.000.000
- Total jumlah seluruh a[i] <= 1.000.000.000
- -1.000.000.000 <= F <= 1.000.000.000

📎 SAMPLE INPUT 1:
4 2 0
4 1 2 3

📎 SAMPLE OUTPUT 1:
50 2

[Penjelasan Sample 1:
F = 0 (tanpa biaya tetap bus).
Jika 1 bus: bobot = 10, biaya = 10^2 = 100.
Jika 2 bus: [4, 1] dan [2, 3], biaya = 25 + 25 = 50.
Biaya minimum = 50 dengan 2 bus.]

📎 SAMPLE INPUT 2:
1 1 100
7

📎 SAMPLE OUTPUT 2:
149 1

[Penjelasan Sample 2:
1 bus: biaya beban = 7^2 = 49, biaya bus = 1 * 100 = 100. Total = 149.]

📎 SAMPLE INPUT 3:
3 3 -20
0 0 0

📎 SAMPLE OUTPUT 3:
-60 3

[Penjelasan Sample 3:
Biaya beban 0. Subsidi F = -20 per bus.
Menggunakan 3 bus menghasilkan biaya = 3 * (-20) = -60.]

💡 HINT:
- Pertama, hitung biaya partisi beban murni `dp[g][N]` untuk setiap `1 <= g <= K` menggunakan
  Divide and Conquer DP Optimization.
- Setelah selesai, iterasi seluruh nilai `g` dari 1 hingga K, hitung `dp[g][N] + g * F`.
- Cari nilai terkecil, dengan tie-breaker memilih `g` yang lebih kecil.

🎯 Learning Goals:
- [ ] Menggabungkan hasil D&C DP di semua layer `1 <= g <= K`.
- [ ] Memisahkan optimasi partisi segmen dengan penalti tetap linier per grup.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll fee;
    if (!(cin >> n >> k >> fee)) return 0;

    // TODO: Selesaikan dengan Divide & Conquer DP Optimization

    return 0;
}
