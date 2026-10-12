/*
============================================================
🏋️ Exercise 2: Partisi Barisan dengan Kuadrat Jumlah Minimum (Aliens + CHT)
============================================================
Day: 271 | Difficulty: Hard | Topic: Aliens Trick + Convex Hull Trick
Source: Optimal K-Partition with Quadratic Costs
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array A berukuran N yang berisi bilangan bulat non-negatif: A[0], A[1], ..., A[N-1].
Kamu harus membagi seluruh array tersebut menjadi TEPAT K buah subarray bersebelahan yang tidak kosong:
[0..r_1], [r_1+1..r_2], ..., [r_{K-1}+1..N-1].
Biaya dari sebuah subarray adalah kuadrat dari jumlah elemen-elemen di dalamnya:
`Cost(Subarray) = (sum_{x in Subarray} x)^2`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi array menjadi tepat K subarray!

Karena N, K <= 100.000, solusi DP O(N * K) atau O(N^2) akan TLE.
Gunakan ALIENS TRICK (WQS Binary Search) dikombinasikan dengan CONVEX HULL TRICK (CHT)
untuk mencapai kompleksitas waktu O(N log(MaxCost))!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat non-negatif A[0], A[1], ..., A[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum partisi.

📏 CONSTRAINTS:
- 1 <= K <= N <= 100.000
- 0 <= A[i] <= 10.000

📎 SAMPLE INPUT 1:
3 2
1 2 3

📎 SAMPLE OUTPUT 1:
18

[Penjelasan Sample 1:
Pilihan partisi:
- [1, 2] dan [3] -> (1+2)^2 + (3)^2 = 3^2 + 3^2 = 9 + 9 = 18.
- [1] dan [2, 3] -> (1)^2 + (2+3)^2 = 1 + 25 = 26.
Biaya minimum adalah 18.]

📎 SAMPLE INPUT 2:
4 2
1 1 1 1

📎 SAMPLE OUTPUT 2:
8

[Penjelasan Sample 2:
Bagi menjadi dua segmen berukuran sama: [1, 1] dan [1, 1].
Biaya = 2^2 + 2^2 = 4 + 4 = 8.]

📎 SAMPLE INPUT 3:
4 4
1 1 1 1

📎 SAMPLE OUTPUT 3:
4

[Penjelasan Sample 3:
Bagi menjadi 4 segmen tunggal: [1], [1], [1], [1].
Biaya = 1^2 + 1^2 + 1^2 + 1^2 = 4.]

💡 HINT:
- Fungsi f(k) = biaya partisi minimum dengan k segmen adalah fungsi konveks terhadap k.
- Hilangkan batas K dengan menambahkan biaya penalti lambda >= 0 untuk setiap segmen baru yang dibentuk.
- Untuk nilai penalti lambda tertentu:
  dp[i] = pref[i]^2 + lambda + min_{j < i} { -2 * pref[j] * pref[i] + dp[j] + pref[j]^2 }.
- Transisi ini adalah kueri garis linear:
  kemiringan m = -2 * pref[j] (monoton menurun)
  evaluasi pada x = pref[i] (monoton menaik).
  Gunakan Convex Hull Trick dengan Deque untuk mengevaluasi DP dalam O(N)!
- Binary search nilai penalti lambda dalam rentang [0, pref[N]^2].

🎯 Learning Goals:
- [ ] Menggabungkan Aliens Trick dengan Convex Hull Trick (CHT).
- [ ] Memahami penalti Lagrange pada masalah minimasi dan eliminasi dimensi K.
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
