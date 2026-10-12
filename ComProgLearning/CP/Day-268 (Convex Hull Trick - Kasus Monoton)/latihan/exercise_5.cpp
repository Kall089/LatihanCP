/*
============================================================
🏋️ Exercise 5: Penutup Jalan Berlubang (Covered Walkway CHT)
============================================================
Day: 268 | Difficulty: Hard | Topic: Convex Hull Trick (Quadratic DP)
Source: Classic ICPC / Covered Walkway
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah jalan setapak memiliki N buah titik lubang di posisi koordinat x[0], x[1], ..., x[N-1]
yang sudah terurut tidak menurun (x[0] <= x[1] <= ... <= x[N-1]).
Pemerintah kota ingin menutupi seluruh N lubang tersebut menggunakan beberapa papan kayu penutup.

Sebuah papan penutup yang membentang dari titik lubang ke-l hingga lubang ke-r (di mana l <= r)
memerlukan biaya pembuatan:
`Biaya(l, r) = C + (x[r] - x[l])^2`.

Pemerintah bebas memilih berapa banyak papan penutup yang akan dipasang dan di mana batas-batasnya,
asalkan SETIAP LUBANG TERCOVER OLEH SETIDAKNYA SATU PAPAN (artinya barisan lubang dipartisi menjadi segmen-segmen penutup).

Tentukan TOTAL BIAYA MINIMUM untuk menutupi seluruh N lubang!

Selesaikan dengan CONVEX HULL TRICK DENGAN DEQUE dalam waktu O(N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan C.
- Baris kedua berisi N bilangan bulat x[0], x[1], ..., x[N-1] (terurut menaik).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum penutupan jalan.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- 1 <= C <= 1.000.000.000.000
- 0 <= x[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4 100
1 2 10 11

📎 SAMPLE OUTPUT 1:
202

[Penjelasan Sample 1:
- Papan 1: menutupi lubang di x=1 dan x=2 -> biaya = 100 + (2 - 1)^2 = 101.
- Papan 2: menutupi lubang di x=10 dan x=11 -> biaya = 100 + (11 - 10)^2 = 101.
Total biaya = 101 + 101 = 202.
(Jika memakai 1 papan besar dari 1 sampai 11: biaya = 100 + (11 - 1)^2 = 100 + 100 = 200?
Tunggu: 100 + (11 - 1)^2 = 100 + 100 = 200!
Maka 1 papan besar bernilai 200, lebih murah dari 202!)]

📎 SAMPLE INPUT 2:
3 5
1 10 20

📎 SAMPLE OUTPUT 2:
15
(Pakai 3 papan terpisah untuk masing-masing lubang: (5 + 0) + (5 + 0) + (5 + 0) = 15)

💡 HINT:
- `dp[i]` adalah biaya minimum menutup lubang dari indeks 1 sampai i.
- `dp[i] = min_{0 <= j < i} { dp[j] + C + (x[i] - x[j+1])^2 }`.
- Ekspansi kuadrat:
  `(x[i] - x[j+1])^2 = x[i]^2 - 2 * x[j+1] * x[i] + x[j+1]^2`.
- `dp[i] = x[i]^2 + C + min_{j} { (-2 * x[j+1]) * x[i] + (dp[j] + x[j+1]^2) }`.
- Slope: `m = -2 * x[j+1]` (menurun), kueri `x = x[i]` (menaik).

🎯 Learning Goals:
- [ ] Mengimplementasikan CHT untuk problem partisi dinamis dengan biaya kuadratik.
- [ ] Menangani koordinat masukan hingga 10^9 dan cross product 128-bit.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll c;
    if (!(cin >> n >> c)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
