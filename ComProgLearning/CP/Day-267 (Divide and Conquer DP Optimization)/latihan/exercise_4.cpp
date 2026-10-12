/*
============================================================
🏋️ Exercise 4: Partisi Varians Minimum (Minimum Variance Partition)
============================================================
Day: 267 | Difficulty: Hard | Topic: Divide & Conquer DP Optimization
Source: Classic D&C DP / Codeforces 321E Style
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan barisan N bilangan bulat a[0], a[1], ..., a[N-1] yang telah terurut tidak menurun (a[0] <= a[1] <= ... <= a[N-1]).
Kamu harus membagi barisan tersebut menjadi TEPAT K segmen berurutan tak kosong.
Biaya suatu segmen [l..r] didefinisikan sebagai jumlah kuadrat selisih antar setiap pasangan elemen di dalam segmen:
`Cost(l, r) = sum_{l <= i < j <= r} (a[i] - a[j])^2`.

Secara aljabar, rumus tersebut dapat dihitung dalam O(1) menggunakan prefix sum:
`Cost(l, r) = (r - l + 1) * (sum_{i=l}^r a[i]^2) - (sum_{i=l}^r a[i])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh N elemen menjadi tepat K segmen!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat non-negatif a[0], a[1], ..., a[N-1] (sudah terurut menaik).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum.

📏 CONSTRAINTS:
- 1 <= K <= min(N, 30)
- 1 <= N <= 20.000
- 0 <= a[i] <= 10.000

📎 SAMPLE INPUT 1:
4 2
1 2 4 5

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Bagi menjadi [1, 2] dan [4, 5]:
- Segmen 1 [1, 2]: (1 - 2)^2 = 1
- Segmen 2 [4, 5]: (4 - 5)^2 = 1
Total biaya = 1 + 1 = 2.]

📎 SAMPLE INPUT 2:
3 1
1 2 3

📎 SAMPLE OUTPUT 2:
6

[Penjelasan Sample 2:
1 segmen: (1 - 2)^2 + (1 - 3)^2 + (2 - 3)^2 = 1 + 4 + 1 = 6.]

📎 SAMPLE INPUT 3:
5 5
1 2 3 4 5

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Gunakan dua array prefix sum:
  1. `pref[i] = sum_{p=1}^i a[p]`
  2. `pref_sq[i] = sum_{p=1}^i a[p]^2`
- Biaya segmen `[l..r]`:
  `len = r - l + 1`
  `sum_sq = pref_sq[r] - pref_sq[l-1]`
  `sum_val = pref[r] - pref[l-1]`
  `Cost(l, r) = len * sum_sq - sum_val * sum_val`.
- Fungsi biaya ini memenuhi sifat Monge / Quadrangle Inequality, sehingga transisi optimal monoton.

🎯 Learning Goals:
- [ ] Mengoptimasi perhitungan varians / pairwise squared difference menggunakan dua prefix sum dalam O(1).
- [ ] Menerapkan D&C DP pada fungsi biaya tingkat lanjut.
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
