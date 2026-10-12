/*
============================================================
🏋️ Exercise 5: Penempatan K Stasiun Relai Sinyal (Aliens + CHT)
============================================================
Day: 271 | Difficulty: Hard | Topic: Aliens Trick + CHT
Source: Signal Booster Relay Optimization
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Jalur transmisi data berjarak L meter memiliki N titik potensial penempatan stasiun pada koordinat:
0 = d[0] < d[1] < ... < d[N-1] = L.
Kita harus mengirimkan paket data dari titik awal d[0] ke titik akhir d[N-1] melalui TEPAT K lompatan/segmen
transmisi (memilih K-1 stasiun perantara di antara {d[1], ..., d[N-2]}).
Distorsi energi pada lompatan dari d[j] ke d[i] (dengan j < i) sebanding dengan kuadrat jarak:
`Distorsi = (d[i] - d[j])^2`.

Tentukan TOTAL DISTORSI MINIMUM untuk transmisi data dengan tepat K lompatan!

Selesaikan dengan ALIENS TRICK (WQS Binary Search) + CONVEX HULL TRICK (CHT)
dalam waktu O(N log(L^2))!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat d[0], d[1], ..., d[N-1] (terurut menaik, d[0] = 0).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total distorsi minimum.

📏 CONSTRAINTS:
- 2 <= N <= 100.000
- 1 <= K <= N - 1
- 0 = d[0] < d[1] < ... < d[N-1] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4 2
0 2 5 10

📎 SAMPLE OUTPUT 1:
50

[Penjelasan Sample 1:
Pilih stasiun perantara di d = 5:
- Lompatan 1: 0 ke 5 -> distorsi (5 - 0)^2 = 25.
- Lompatan 2: 5 ke 10 -> distorsi (10 - 5)^2 = 25.
Total distorsi = 25 + 25 = 50.
(Jika memilih d = 2: (2-0)^2 + (10-2)^2 = 4 + 64 = 68 > 50).]

📎 SAMPLE INPUT 2:
4 3
0 2 5 10

📎 SAMPLE OUTPUT 2:
38

[Penjelasan Sample 2:
K = 3 berarti kita singgah di semua stasiun:
(2 - 0)^2 + (5 - 2)^2 + (10 - 5)^2 = 4 + 9 + 25 = 38.]

📎 SAMPLE INPUT 3:
4 1
0 2 5 10

📎 SAMPLE OUTPUT 3:
100

[Penjelasan Sample 3:
Hanya 1 lompatan langsung dari 0 ke 10: (10 - 0)^2 = 100.]

💡 HINT:
- Fungsi f(k) = distorsi minimum dengan k lompatan bersifat konveks terhadap k.
- Hilangkan batas K dengan penalti biaya lambda >= 0 per lompatan.
- Transisi DP:
  dp[i] = d[i]^2 + lambda + min_{0 <= j < i} { -2 * d[i] * d[j] + dp[j] + d[j]^2 }.
- Kemiringan m = -2 * d[j] menurun, query x = d[i] menaik -> Deque CHT dalam O(N).
- Binary search lambda pada rentang [0, d[N-1]^2].

🎯 Learning Goals:
- [ ] Mengaplikasikan Aliens Trick pada optimasi rute lompatan diskret.
- [ ] Mengontrol jumlah lompatan K secara presisi menggunakan relaksasi Lagrange.
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(L^2))

    return 0;
}
