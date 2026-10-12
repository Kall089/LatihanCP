/*
============================================================
🏋️ Exercise 2: Katak dan Batu Berkabut (Frog 3 with CHT)
============================================================
Day: 268 | Difficulty: Medium | Topic: Convex Hull Trick (Dynamic DP)
Source: Educational DP Contest Z (Frog 3)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seekor katak berada di atas batu nomor 1 dari N buah batu yang berjejer.
Ketinggian batu ke-i adalah h[i]. Ketinggian batu diketahui TIDAK PERNAH MENURUN (h[0] <= h[1] <= ... <= h[N-1]).
Katak ingin melompat mencapai batu ke-N.
Dari batu j, katak dapat melompat langsung ke batu i mana pun asalkan j < i.
Biaya satu lompatan dari batu j ke batu i adalah:
`Biaya(j, i) = (h[i] - h[j])^2 + C`.

Tentukan TOTAL BIAYA MINIMUM yang harus dikeluarkan katak untuk mencapai batu ke-N!
(Jika N = 1, katak sudah di tujuan, total biaya = 0).

Selesaikan dengan CONVEX HULL TRICK DENGAN DEQUE dalam waktu O(N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan C.
- Baris kedua berisi N bilangan bulat h[0], h[1], ..., h[N-1] (ketinggian terurut tidak menurun).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: biaya minimum mencapai batu ke-N.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000 <= h[i] <= 1.000.000
- 0 <= C <= 1.000.000.000.000

📎 SAMPLE INPUT 1:
4 5
1 3 4 10

📎 SAMPLE OUTPUT 1:
55

[Penjelasan Sample 1:
Lompat 1 -> 2: (3 - 1)^2 + 5 = 9.
Lompat 2 -> 3: (4 - 3)^2 + 5 = 6. (Total sampai batu 3 = 15).
Atau lompat langsung 1 -> 3: (4 - 1)^2 + 5 = 14 (lebih murah!).
Dari batu 3 -> 4: (10 - 4)^2 + 5 = 36 + 5 = 41. Total = 14 + 41 = 55.]

📎 SAMPLE INPUT 2:
1 100
5

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
3 0
2 2 2

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Rekurensi DP:
  `dp[i] = min_{0 <= j < i} { dp[j] + (h[i] - h[j])^2 + C }`.
- Ekspansi:
  `(h[i] - h[j])^2 = h[i]^2 - 2 * h[j] * h[i] + h[j]^2`.
- Bentuk garis dari j:
  `slope m_j = -2 * h[j]`, `intercept b_j = dp[j] + h[j]^2`.
- Query pada i:
  `x = h[i]`, tambahkan `h[i]^2 + C` ke hasil minimum query.
- Karena h tidak menurun, slope `m = -2 * h` tidak menaik dan kueri `x = h` tidak menurun!
  Kondisi CHT monoton terpenuhi sempurna!

🎯 Learning Goals:
- [ ] Mengaljabarkan persamaan kuadrat DP ke dalam formulasi garis linear CHT.
- [ ] Melakukan integrasi penambahan garis state j secara dinamis saat iterasi berjalan.
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

    // TODO: Selesaikan dengan Dynamic CHT Deque

    return 0;
}
