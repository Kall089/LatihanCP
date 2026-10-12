/*
============================================================
🏋️ Exercise 1: Peti yang Hanya Bisa Digabung dari Samping
============================================================
Day: 270 | Difficulty: Medium | Topic: Knuth Optimization (Sequential Merging)
Source: Classic Knuth DP (Garsia-Wachs Variant)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N buah peti barang yang berjejer dalam satu baris dari kiri ke kanan.
Peti ke-i memiliki bobot a[i].
Kamu ingin menggabungkan seluruh N peti tersebut menjadi satu peti raksasa melalui serangkaian penggabungan.

Dalam satu operasi penggabungan:
- Kamu memilih dua kelompok peti yang saling BERSEBELAHAN (adjacent).
- Menggabungkan keduanya menjadi satu kelompok baru.
- Biaya yang harus dibayar adalah JUMLAH SELURUH BOBOT PETI pada kedua kelompok yang digabung tersebut.
- Urutan relatif peti tidak boleh diubah (tidak boleh menukar posisi peti).

Tentukan TOTAL BIAYA MINIMUM untuk menggabungkan seluruh peti menjadi satu!

Selesaikan dengan KNUTH OPTIMIZATION dalam waktu O(N^2)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat non-negatif a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum penggabungan.

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 0 <= a[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
4 1 2 3

📎 SAMPLE OUTPUT 1:
19

[Penjelasan Sample 1:
- Gabung peti 1 & 2 (bobot 1 dan 2): biaya = 1 + 2 = 3. Barisan menjadi [4, (3), 3].
- Gabung kelompok (3) & 3 (bobot 3 dan 3): biaya = 3 + 3 = 6. Barisan menjadi [4, (6)].
- Gabung 4 & (6): biaya = 4 + 6 = 10.
Total biaya = 3 + 6 + 10 = 19.]

📎 SAMPLE INPUT 2:
1
9

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
4
0 0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Definisikan `dp[l][r]` sebagai biaya minimum menggabungkan peti l..r menjadi satu.
- Rekurensi: `dp[l][r] = sum(l, r) + min_{l <= k < r} (dp[l][k] + dp[k+1][r])`.
- Karena fungsi biaya `C(l, r) = sum(l, r)` memenuhi Quadrangle Inequality, titik potong optimal `opt[l][r]`
  memenuhi syarat Knuth: `opt[l][r-1] <= opt[l][r] <= opt[l+1][r]`.
- Loop panjang interval len dari 2 sampai N.
- Batasi pencarian k pada `[opt[l][r-1], opt[l+1][r]]`.

🎯 Learning Goals:
- [ ] Memahami implementasi Knuth Optimization untuk Range DP.
- [ ] Memverifikasi sifat teleskopik yang memangkas waktu dari O(N^3) ke O(N^2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
