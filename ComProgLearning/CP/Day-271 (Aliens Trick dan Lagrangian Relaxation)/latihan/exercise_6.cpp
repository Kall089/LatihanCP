/*
============================================================
🏋️ Exercise 6: Partisi Barisan dengan Biaya Kuadratik dan Biaya Tetap Segmen
============================================================
Day: 271 | Difficulty: Menantang | Topic: Aliens Trick + CHT
Source: Optimal Partition with Quadratic and Fixed Overhead
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array A berukuran N yang berisi bilangan bulat non-negatif: A[0], A[1], ..., A[N-1].
Array harus dibagi menjadi TEPAT K buah subarray bersebelahan yang tidak kosong.
Setiap kali sebuah subarray [l..r] dibentuk, biaya yang dikeluarkan adalah kuadrat dari jumlah elemennya
DITAMBAH biaya overhead tetap per segmen sebesar C_fixed:
`Cost(l, r) = (sum_{t=l}^r A[t])^2 + C_fixed`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi array menjadi tepat K subarray!

Selesaikan dengan ALIENS TRICK (WQS Binary Search) + CONVEX HULL TRICK (CHT)
dalam waktu O(N log(MaxCost))!

📥 INPUT FORMAT:
- Baris pertama berisi tiga bilangan bulat N, K, dan C_fixed.
- Baris kedua berisi N bilangan bulat non-negatif A[0], A[1], ..., A[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum partisi.

📏 CONSTRAINTS:
- 1 <= K <= N <= 100.000
- 0 <= C_fixed <= 1.000.000.000
- 0 <= A[i] <= 10.000

📎 SAMPLE INPUT 1:
3 2 10
1 2 3

📎 SAMPLE OUTPUT 1:
38

[Penjelasan Sample 1:
Pilihan partisi terbaik: [1, 2] dan [3].
- Biaya segmen 1: (1 + 2)^2 + 10 = 9 + 10 = 19.
- Biaya segmen 2: (3)^2 + 10 = 9 + 10 = 19.
Total biaya = 19 + 19 = 38.
(Tanpa C_fixed, biayanya adalah 18. Karena ada tepat K = 2 segmen, tambahan biaya overhead adalah 2 * 10 = 20 -> 18 + 20 = 38).]

📎 SAMPLE INPUT 2:
4 2 5
1 1 1 1

📎 SAMPLE OUTPUT 2:
18

[Penjelasan Sample 2:
Partisi [1, 1] dan [1, 1]: biaya dasar = 2^2 + 2^2 = 8.
Ditambah overhead 2 * 5 = 10 -> total = 8 + 10 = 18.]

💡 HINT:
- Karena jumlah segmen bernilai TEPAT K, total biaya overhead tetap adalah konstan: K * C_fixed.
- Masalah ini ekivalen dengan meminimalkan kuadrat jumlah segmen (Exercise 2) lalu menambahkan K * C_fixed,
  atau menyerap C_fixed ke dalam penalti lambda: lambda_effective = C_fixed + lambda.
- Gunakan Aliens Trick + CHT persis seperti pada Exercise 2.

🎯 Learning Goals:
- [ ] Memahami sifat invariansi penalti linier tetap pada masalah pembatasan eksak K.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll c_fixed;
    if (!(cin >> n >> k >> c_fixed)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
