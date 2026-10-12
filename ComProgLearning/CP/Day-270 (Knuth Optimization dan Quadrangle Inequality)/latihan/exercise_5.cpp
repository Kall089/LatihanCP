/*
============================================================
🏋️ Exercise 5: Pembangunan Rantai Menara Telekomunikasi
============================================================
Day: 270 | Difficulty: Hard | Topic: Knuth Optimization (Range DP with Base Overhead)
Source: Telecommunication Infrastructure Merging
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N stasiun menara telekomunikasi berurutan dari 1 sampai N di sepanjang jalur kereta api.
Menara ke-i memiliki beban bandwidth harian w[i].
Perusahaan ingin mengintegrasikan seluruh N stasiun menara menjadi satu stasiun induk pusat.

Pengintegrasian dilakukan secara bertahap:
- Setiap langkah memilih dua kelompok menara yang saling bersebelahan.
- Menggabungkan keduanya menjadi satu kelompok terpadu.
- Biaya satu kali penggabungan mencakup total beban bandwidth kedua kelompok DITAMBAH biaya overhead peralatan sebesar K:
  `Biaya(l, r) = sum_{t=l}^r w[t] + K`.
- Urutan posisi menara tidak boleh diubah.

Tentukan TOTAL BIAYA MINIMUM untuk menggabungkan seluruh N menara menjadi satu!

Selesaikan dengan KNUTH OPTIMIZATION dalam waktu O(N^2)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat non-negatif w[0], w[1], ..., w[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum penggabungan.

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 0 <= K <= 1.000.000.000
- 0 <= w[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 10
5 2 4

📎 SAMPLE OUTPUT 1:
37

[Penjelasan Sample 1:
- Langkah 1: Gabung menara 1 dan 2 (beban 2 dan 4). Biaya = (2 + 4) + 10 = 16. Sisa menara [5, (6)].
- Langkah 2: Gabung menara 0 dan kelompok (6) (beban 5 dan 6). Biaya = (5 + 6) + 10 = 21.
Total biaya = 16 + 21 = 37.]

📎 SAMPLE INPUT 2:
1 50
10

📎 SAMPLE OUTPUT 2:
0

💡 HINT:
- Fungsi biaya interval adalah `C(l, r) = (pref[r+1] - pref[l]) + K`.
- Perhatikan: untuk a <= b <= c <= d:
  `C(a, c) + C(b, d) = sum(a, c) + K + sum(b, d) + K = sum(a, d) + sum(b, c) + 2K = C(a, d) + C(b, c)`.
  Persamaan Quadrangle Inequality tetap terpenuhi secara sempurna!
- Karena K >= 0 dan w[i] >= 0, monotonisitas juga terpenuhi.
- Terapkan Knuth Optimization: `opt[l][r-1] <= opt[l][r] <= opt[l+1][r]`.

🎯 Learning Goals:
- [ ] Membuktikan bahwa penambahan konstanta overhead K tetap memenuhi Quadrangle Inequality.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
