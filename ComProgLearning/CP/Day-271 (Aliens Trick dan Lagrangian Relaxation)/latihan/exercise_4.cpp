/*
============================================================
🏋️ Exercise 4: Menutupi Titik dengan K Foto Kuadrat (IOI 2016 Aliens 1D)
============================================================
Day: 271 | Difficulty: Hard | Topic: Aliens Trick + CHT
Source: IOI 2016 Aliens (1D Projection Variant)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N titik pada garis bilangan: x[0] < x[1] < ... < x[N-1].
Kamu ditugaskan untuk menutupi seluruh N titik tersebut menggunakan PALING BANYAK K buah foto kuadrat.
Sebuah foto yang menutupi sekelompok titik dari x[j] sampai x[i] (dengan j <= i) memiliki
panjang sisi (x[i] - x[j] + 1) dan luas kuadrat:
`Luas = (x[i] - x[j] + 1)^2`.
Seluruh titik harus tercover oleh setidaknya satu foto.
Tentukan TOTAL LUAS FOTO MINIMUM untuk menutupi seluruh N titik dengan paling banyak K foto!

Selesaikan dengan ALIENS TRICK (WQS Binary Search) + CONVEX HULL TRICK (CHT)
dalam waktu O(N log(MaxArea))!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat x[0], x[1], ..., x[N-1] (terurut menaik).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total luas foto minimum.

📏 CONSTRAINTS:
- 1 <= K <= N <= 100.000
- 1 <= x[0] < x[1] < ... < x[N-1] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 3
1 4 7

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
Gunakan 3 foto berukuran 1x1:
- Foto 1 menutupi titik 1: (1-1+1)^2 = 1.
- Foto 2 menutupi titik 4: (4-4+1)^2 = 1.
- Foto 3 menutupi titik 7: (7-7+1)^2 = 1.
Total luas = 1 + 1 + 1 = 3.]

📎 SAMPLE INPUT 2:
3 1
1 4 7

📎 SAMPLE OUTPUT 2:
49

[Penjelasan Sample 2:
Hanya boleh 1 foto: harus menutupi dari titik 1 sampai 7.
Panjang sisi = 7 - 1 + 1 = 7. Luas = 7^2 = 49.]

📎 SAMPLE INPUT 3:
3 2
1 2 10

📎 SAMPLE OUTPUT 3:
5

[Penjelasan Sample 3:
Foto 1 menutupi [1, 2]: panjang 2 - 1 + 1 = 2 -> luas 4.
Foto 2 menutupi [10]: panjang 10 - 10 + 1 = 1 -> luas 1.
Total luas = 4 + 1 = 5.]

💡 HINT:
- Misalkan f(k) adalah luas minimum dengan k foto. f(k) bersifat konveks.
- Tambahkan penalti biaya lambda >= 0 untuk setiap foto baru yang diambil.
- Formulasi DP dengan penalti lambda:
  dp[i] = (x[i] + 1)^2 + lambda + min_{0 <= j < i} { -2*(x[i] + 1)*x[j+1] + dp[j] + x[j+1]^2 }.
- Transisi ini adalah kueri garis linear:
  kemiringan m = -2 * x[j+1] (monoton menurun)
  evaluasi pada query = x[i] + 1 (monoton menaik).
  Gunakan Deque CHT untuk mengevaluasi DP dalam O(N)!
- Binary search lambda pada rentang [0, (x[N-1] - x[0] + 1)^2].
- Jawaban akhir: dp[N].val - K * lambda*.

🎯 Learning Goals:
- [ ] Menyelesaikan masalah asli IOI 2016 Aliens dengan Aliens Trick.
- [ ] Mengombinasikan Convex Hull Trick dan WQS Binary Search secara terpadu.
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxArea))

    return 0;
}
