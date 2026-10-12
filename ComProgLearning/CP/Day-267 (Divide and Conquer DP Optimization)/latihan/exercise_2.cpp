/*
============================================================
🏋️ Exercise 2: Posko di Jalan Panjang (Median Distance Cost D&C DP)
============================================================
Day: 267 | Difficulty: Hard | Topic: Divide & Conquer DP Optimization
Source: Classic D&C DP / IOI Post Office Style
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N kampung yang terletak di sepanjang jalan lurus, dengan posisi x[0], x[1], ..., x[N-1]
yang sudah terurut tidak menurun (x[0] <= x[1] <= ... <= x[N-1]).
Kamu harus membagi seluruh kampung menjadi TEPAT K wilayah berurutan tak kosong.

Setiap wilayah akan membangun TEPAT SATU posko bantuan pada posisi salah satu kampung di dalam wilayah tersebut.
Biaya satu wilayah adalah TOTAL JARAK DARI SELURUH KAMPUNG DALAM WILAYAH TERSEBUT KE POSKO.
(Secara matematis, untuk meminimalkan jumlah jarak absolut ke satu titik, posko harus diletakkan pada MEDIAN wilayah tersebut).

Tentukan TOTAL BIAYA MINIMUM untuk melayani seluruh kampung dengan tepat K posko!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat non-negatif x[0], x[1], ..., x[N-1] (sudah terurut menaik).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total jarak minimum.

📏 CONSTRAINTS:
- 1 <= K <= min(N, 30)
- 1 <= N <= 20.000
- 0 <= x[i] <= 1.000.000

📎 SAMPLE INPUT 1:
4 2
1 2 3 4

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Bagi menjadi [1, 2] (posko di 1 atau 2, biaya = 1) dan [3, 4] (posko di 3 atau 4, biaya = 1).
Total jarak = 1 + 1 = 2.]

📎 SAMPLE INPUT 2:
1 1
7

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Hanya 1 kampung, posko di kampung itu sendiri, jarak = 0.]

📎 SAMPLE INPUT 3:
3 3
0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Untuk segmen kampung [l..r], posisi posko optimal adalah median di indeks `m = (l + r) / 2`.
- Biaya segmen [l..r] dapat dihitung dalam O(1) menggunakan prefix sum:
  `Cost(l, r) = x[m] * (m - l + 1) - sum(l..m) + sum(m..r) - x[m] * (r - m)`.
- Fungsi biaya median terbukti memenuhi Quadrangle Inequality (Sifat Monge),
  sehingga transisi optimal monoton dan dapat dioptimasi dengan D&C DP.

🎯 Learning Goals:
- [ ] Menghitung biaya jarak ke median dalam O(1) menggunakan prefix sum.
- [ ] Mengaplikasikan D&C DP optimization pada permasalahan penempatan fasilitas (*post office problem*).
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
