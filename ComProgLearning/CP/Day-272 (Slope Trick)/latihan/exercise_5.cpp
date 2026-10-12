/*
============================================================
🏋️ Exercise 5: Penataan Barisan dengan Batas Selisih Umum [D_min, D_max]
============================================================
Day: 272 | Difficulty: Hard | Topic: Slope Trick (General Delta Bounds)
Source: General Interval Minkowski Convolution
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan barisan target A = [a_0, a_1, ..., a_{N-1}] dan dua batas bilangan bulat D_min <= D_max.
Kamu ingin menentukan barisan bilangan bulat baru B = [b_0, b_1, ..., b_{N-1}] sedemikian sehingga:
1. Selisih antar elemen bersebelahan berada dalam rentang yang diizinkan:
   D_min <= b_i - b_{i-1} <= D_max, untuk setiap i = 1, 2, ..., N-1.
2. Total biaya perubahan, yaitu sum_{i=0}^{N-1} |a_i - b_i|, bernilai sekecil mungkin.

Selesaikan masalah ini dengan SLOPE TRICK 2-Heap dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi tiga bilangan bulat N, D_min, dan D_max.
- Baris kedua berisi N bilangan bulat a_0, a_1, ..., a_{N-1}.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum.

📏 CONSTRAINTS:
- 1 <= N <= 100.000
- -1.000.000.000 <= D_min <= D_max <= 1.000.000.000
- -1.000.000.000 <= a_i <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 -5 5
0 10 20

📎 SAMPLE OUTPUT 1:
10

[Penjelasan Sample 1:
Dengan selisih antara -5 dan 5, pilih b = [5, 10, 15] -> biaya = 5 + 0 + 5 = 10.]

📎 SAMPLE INPUT 2:
4 1 1000000000
2 1 5 11

📎 SAMPLE OUTPUT 2:
2

[Penjelasan Sample 2:
D_min = 1 dan D_max = 10^9 merepresentasikan syarat strictly increasing (b_i - b_{i-1} >= 1).
Biaya minimum = 2.]

📎 SAMPLE INPUT 3:
5 0 1000000000
5 4 3 2 1

📎 SAMPLE OUTPUT 3:
6

[Penjelasan Sample 3:
D_min = 0 dan D_max = 10^9 merepresentasikan syarat non-decreasing (b_i - b_{i-1} >= 0).
Biaya minimum = 6.]

💡 HINT:
- Rekurensi DP:
  dp[i](x) = |x - a_i| + min_{y in [x - D_max, x - D_min]} dp[i-1](y).
- Operasi konvolusi infimal dengan interval [D_min, D_max] menggeser seluruh lereng kiri (L)
  sebesar D_min dan seluruh lereng kanan (R) sebesar D_max:
  tag_L += D_min
  tag_R += D_max
- Tambahkan fungsi nilai mutlak |x - a_i| ke struktur data 2-heap dengan memperhitungkan tag_L dan tag_R.

🎯 Learning Goals:
- [ ] Menyatukan berbagai variasi konstrain barisan monoton dan berjarak terbatas ke dalam satu kerangka Minkowski Sum Slope Trick.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll d_min, d_max;
    if (!(cin >> n >> d_min >> d_max)) return 0;

    // TODO: Selesaikan dengan General Slope Trick O(N log N)

    return 0;
}
