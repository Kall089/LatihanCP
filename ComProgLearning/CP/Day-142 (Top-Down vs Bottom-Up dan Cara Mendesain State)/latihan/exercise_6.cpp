#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 6: Lampu Taman Sejumlah K (Counting DP dengan Syarat Multi-Dimensi)
 *
 * Di sepanjang jalan taman terdapat N tiang lampu yang berjajar lurus (tiang 1 sampai N).
 * Pengelola taman ingin menyalakan TEPAT K tiang lampu.
 *
 * Namun, karena alasan estetika dan penghematan daya, terdapat aturan ketat:
 * TIDAK BOLEH ADA DUA TIANG LAMPU YANG BERSEBELAHAN KEDUANYA MENYALA.
 *
 * Hitung ada berapa banyak konfigurasi berbeda dalam memilih K tiang lampu tersebut.
 * Karena jumlahnya bisa sangat besar, keluarkan hasil modulo 1.000.000.007.
 *
 * Catatan Khusus:
 * Jika N = 0 dan K = 0, terdapat tepat 1 konfigurasi (yaitu konfigurasi himpunan kosong).
 *
 * Format Input:
 * Satu baris berisi dua bilangan bulat N dan K.
 *
 * Format Output:
 * Satu bilangan bulat: banyak konfigurasi valid modulo 1.000.000.007.
 *
 * Batasan:
 * 0 <= N <= 1.000
 * 0 <= K <= N
 *
 * Test Case 1:
 * Input:
 * 5 2
 * Output:
 * 6
 * Penjelasan:
 * Konfigurasi 5 tiang dengan 2 lampu tanpa ada yang bersebelahan:
 * 1) [1, 3] -> 10100
 * 2) [1, 4] -> 10010
 * 3) [1, 5] -> 10001
 * 4) [2, 4] -> 01010
 * 5) [2, 5] -> 01001
 * 6) [3, 5] -> 00101
 * Total = 6 konfigurasi.
 *
 * Test Case 2:
 * Input:
 * 3 2
 * Output:
 * 1
 * Penjelasan:
 * Hanya ada 1 pilihan yaitu tiang 1 dan tiang 3 (pola: 101).
 *
 * Test Case 3:
 * Input:
 * 0 0
 * Output:
 * 1
 * Penjelasan:
 * Tiang kosong dengan 0 lampu menyala memiliki tepat 1 cara.
 *
 * Hint 1:
 * Pertanyaan "apakah tiang i boleh dinyalakan?" hanya bergantung pada satu hal:
 * APAKAH TIANG i-1 SEDANG MENYALA ATAU PADAM?
 *
 * Hint 2:
 * Rancang state 3 dimensi:
 * dp[i][j][0] = banyak cara mengatur i tiang dengan j lampu menyala, di mana tiang ke-i PADAM.
 * dp[i][j][1] = banyak cara mengatur i tiang dengan j lampu menyala, di mana tiang ke-i MENYALA.
 *
 * Hint 3:
 * Transisi untuk tiang ke-i:
 * - Jika tiang i padam: tiang i-1 boleh padam atau menyala.
 *   dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD
 * - Jika tiang i menyala: tiang i-1 HARUS padam, dan kita menambah 1 lampu menyala.
 *   dp[i][j][1] = dp[i-1][j-1][0] % MOD (untuk j >= 1)
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Implementasikan Counting DP modulo 10^9 + 7
    // Perhatikan basis n = 0, k = 0
    // Gunakan nested loop dan operasi modulo pada setiap penjumlahan

    return 0;
}
