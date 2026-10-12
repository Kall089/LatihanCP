/*
============================================================
🏋️ Exercise 6: Optimal Stock Trading (CF 865D Buy Low Sell High)
============================================================
Day: 272 | Difficulty: Menantang | Topic: Slope Trick (Concave Profit Maximization)
Source: Codeforces 865D - Buy Low Sell High
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu dapat meramalkan harga saham selama N hari ke depan: P[0], P[1], ..., P[N-1].
Pada hari ke-i, kamu dapat memilih tepat salah satu dari tiga tindakan:
1. Membeli 1 lembar saham dengan harga P[i].
2. Menjual 1 lembar saham dengan harga P[i] (hanya boleh jika kamu saat itu memegang setidaknya 1 saham).
3. Tidak melakukan apa-apa.

Pada awalnya kamu tidak memiliki saham dan di akhir hari ke-(N-1) kamu boleh memegang atau tidak memegang saham.
Tentukan TOTAL KEUNTUNGAN MAKSIMUM yang dapat kamu peroleh!

Selesaikan masalah ini dengan SLOPE TRICK / REGRET GREEDY dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat positif P[0], P[1], ..., P[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: keuntungan maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 300.000
- 1 <= P[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
1 2 10 9

📎 SAMPLE OUTPUT 1:
16

[Penjelasan Sample 1:
Beli di hari 0 (harga 1) dan jual di hari 2 (harga 10) -> keuntungan = 10 - 1 = 9.
Beli di hari 1 (harga 2) dan jual di hari 3 (harga 9) -> keuntungan = 9 - 2 = 7.
Total keuntungan = 9 + 7 = 16.]

📎 SAMPLE INPUT 2:
9
10 5 4 7 9 12 6 2 10

📎 SAMPLE OUTPUT 2:
20

[Penjelasan Sample 2:
Transaksi optimal:
- Beli di harga 4, jual di harga 12 -> untung 8.
- Beli di harga 5, jual di harga 9 -> untung 4.
- Beli di harga 2, jual di harga 10 -> untung 8.
Total keuntungan = 8 + 4 + 8 = 20.]

💡 HINT:
- Masalah ini dapat dipandang sebagai memelihara fungsi keuntungan DP terhadap jumlah saham yang dipegang.
- Fungsi f_i(s) = profit maksimum memegang s saham adalah fungsi konkaf sepotong-sepotong.
- Setiap hari i:
  - Kita dapat membeli saham di harga P[i] (dorong P[i] ke Min-Heap sebagai opsi beli).
  - Jika harga beli termurah di heap `pq.top() < P[i]`:
    Ambil keputusan awal: "beli di pq.top() dan jual di P[i]".
    Keuntungan bertambah P[i] - pq.top().
    Namun, di masa depan mungkin ada hari dengan harga lebih tinggi dari P[i].
    Untuk mengizinkan "membatalkan" penjualan di P[i] dan menjualnya di hari nanti yang lebih mahal,
    kita pop pq.top() dan dorong P[i] kembali ke heap!
  - Dorong juga P[i] sebagai opsi pembelian baru di hari i.

🎯 Learning Goals:
- [ ] Memahami hubungan antara Slope Trick dan strategi Regret Greedy (buy low, sell high).
- [ ] Menyelesaikan Codeforces 865D dengan implementasi elegan O(N log N).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
