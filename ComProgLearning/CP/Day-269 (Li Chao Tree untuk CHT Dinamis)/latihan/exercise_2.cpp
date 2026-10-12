/*
============================================================
🏋️ Exercise 2: Katak di Pegunungan Acak (Non-Monotone Frog Jump)
============================================================
Day: 269 | Difficulty: Hard | Topic: Li Chao Tree (Dynamic DP)
Source: Educational DP Contest Z Variant (Arbitrary Heights)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seekor katak berada di atas batu nomor 1 dari N buah batu yang berjejer.
Ketinggian batu ke-i adalah h[i]. Namun kali ini, KETINGGIAN BATU TIDAK HARUS TERURUT (bebas naik dan turun)!
Urutan indeks batu 1, 2, ..., N tetap tidak boleh diubah.

Katak ingin melompat mencapai batu ke-N.
Dari batu j, katak dapat melompat ke batu i mana pun asalkan j < i.
Biaya satu lompatan dari batu j ke batu i adalah:
`Biaya(j, i) = (h[i] - h[j])^2 + C`.

Tentukan TOTAL BIAYA MINIMUM untuk mencapai batu ke-N!
(Jika N = 1, total biaya = 0).

Selesaikan dengan LI CHAO TREE dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan C.
- Baris kedua berisi N bilangan bulat h[0], h[1], ..., h[N-1] (ketinggian acak).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: biaya minimum mencapai batu ke-N.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000 <= h[i] <= 1.000.000
- 0 <= C <= 1.000.000.000.000

📎 SAMPLE INPUT 1:
4 5
1 10 3 8

📎 SAMPLE OUTPUT 1:
39

[Penjelasan Sample 1:
Batu 1 (h=1), Batu 2 (h=10), Batu 3 (h=3), Batu 4 (h=8).
- dp[0] = 0 (batu 1).
- Lompat 1 -> 3: (3 - 1)^2 + 5 = 9.
- Lompat 3 -> 4: (8 - 3)^2 + 5 = 25 + 5 = 30. Total = 9 + 30 = 39.
(Jika lompat 1 -> 4 langsung: (8 - 1)^2 + 5 = 49 + 5 = 54 > 39).]

📎 SAMPLE INPUT 2:
1 20
4

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
3 0
2 2 2

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Rekurensi:
  `dp[i] = h[i]^2 + C + min_{j < i} { (-2 * h[j]) * h[i] + (dp[j] + h[j]^2) }`.
- Karena h[i] tidak terurut naik, CHT Deque TIDAK DAPAT DIGUNAKAN!
- Kumpulkan seluruh nilai h[i] sebagai himpunan titik kueri Li Chao Tree.
- Masukkan garis `Line(-2 * h[j], dp[j] + h[j]^2)` ke dalam Li Chao Tree setelah menghitung `dp[j]`.

🎯 Learning Goals:
- [ ] Menerapkan Li Chao Tree untuk menyelesaikan DP kuadratik pada data non-monoton.
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

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
