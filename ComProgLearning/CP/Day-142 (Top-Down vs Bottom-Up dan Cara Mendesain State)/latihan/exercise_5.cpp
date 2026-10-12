#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 5: Jual Beli Saham dengan Cooldown (State Machine DP)
 *
 * Diberikan array harga saham selama N hari, di mana price[i] adalah harga saham pada hari ke-i.
 * Kamu ingin merancang strategi perdagangan untuk memaksimalkan total keuntungan dengan aturan:
 * 1. Kamu hanya boleh memegang maksimal 1 lembar saham pada satu waktu (kamu harus menjual
 *    saham yang sedang dipegang sebelum boleh membeli saham baru).
 * 2. Kamu boleh melakukan transaksi (beli lalu jual) sebanyak yang kamu mau.
 * 3. Aturan Cooldown: Setelah kamu menjual saham pada hari i, kamu TIDAK BOLEH membeli saham
 *    pada hari berikutnya (hari i+1). Kamu baru boleh membeli saham lagi paling cepat pada hari i+2.
 *
 * Hitung total keuntungan maksimum yang dapat kamu peroleh.
 *
 * Format Input:
 * Baris pertama berisi satu bilangan bulat N.
 * Baris kedua berisi N bilangan bulat price[0], price[1], ..., price[N-1].
 *
 * Format Output:
 * Satu bilangan bulat: total keuntungan maksimum.
 *
 * Batasan:
 * 1 <= N <= 100.000
 * 0 <= price[i] <= 10.000
 *
 * Test Case 1:
 * Input:
 * 5
 * 1 2 3 0 2
 * Output:
 * 3
 * Penjelasan:
 * Hari 0: Beli di harga 1
 * Hari 1: Jual di harga 2 (untung +1)
 * Hari 2: Cooldown (wajib istirahat setelah menjual di hari 1)
 * Hari 3: Beli di harga 0
 * Hari 4: Jual di harga 2 (untung +2)
 * Total keuntungan = 1 + 2 = 3.
 *
 * Test Case 2:
 * Input:
 * 1
 * 1
 * Output:
 * 0
 * Penjelasan:
 * Hanya ada 1 hari, tidak ada kesempatan menghasilkan keuntungan.
 *
 * Test Case 3:
 * Input:
 * 5
 * 7 6 4 3 1
 * Output:
 * 0
 * Penjelasan:
 * Harga terus turun setiap hari, strategi terbaik adalah tidak melakukan transaksi apa pun.
 *
 * Hint 1:
 * Masalah ini memiliki 3 keadaan (state) di akhir setiap hari:
 * - HOLD: sedang memegang saham.
 * - SOLD: baru saja menjual saham hari ini (besok wajib cooldown).
 * - REST: tidak memegang saham dan bebas untuk membeli (cooldown sudah selesai atau tidak ada aksi).
 *
 * Hint 2:
 * Pikirkan diagram transisi antar status (Finite State Machine):
 * - hold[i] = max(hold[i-1], rest[i-1] - price[i])
 * - sold[i] = hold[i-1] + price[i]
 * - rest[i] = max(rest[i-1], sold[i-1])
 *
 * Hint 3:
 * Inisialisasi hari 0:
 * hold[0] = -price[0] (beli saham hari pertama)
 * sold[0] = 0
 * rest[0] = 0
 * Jawaban akhir adalah max(sold[N-1], rest[N-1]).
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }

    // TODO: Implementasikan FSM DP dengan 3 state (hold, sold, rest)
    // Manfaatkan rolling variable untuk mendapatkan solusi O(1) space!

    return 0;
}
