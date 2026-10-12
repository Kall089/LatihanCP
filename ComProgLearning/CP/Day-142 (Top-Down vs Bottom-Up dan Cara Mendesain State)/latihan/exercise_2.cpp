#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 2: Lompat Katak dengan K Langkah (Frog 2 - AtCoder DP-B)
 *
 * Seekor katak berada di batu ke-1 (indeks 0) dan ingin mencapai batu ke-N (indeks N-1).
 * Terdapat N batu dengan tinggi masing-masing h[0], h[1], ..., h[N-1].
 * Berbeda dengan latihan sebelumnya, kali ini dari batu i katak boleh melompat
 * sejauh 1, 2, ..., hingga maksimal K batu ke depan (yaitu ke batu i+1, i+2, ..., i+K).
 * Biaya energi yang dikeluarkan untuk melompat dari batu i ke batu j adalah |h[i] - h[j]|.
 * Hitung total biaya energi minimum yang dibutuhkan katak untuk mencapai batu ke-N.
 *
 * Perhatikan bahwa transisi sekarang melibatkan loop dinamis sebanyak min(i, K).
 *
 * Format Input:
 * Baris pertama berisi dua bilangan bulat N dan K.
 * Baris kedua berisi N bilangan bulat h[0], h[1], ..., h[N-1].
 *
 * Format Output:
 * Satu bilangan bulat: total biaya energi minimum.
 *
 * Batasan:
 * 2 <= N <= 100.000
 * 1 <= K <= 100
 * 1 <= h[i] <= 10.000
 *
 * Test Case 1:
 * Input:
 * 5 3
 * 10 30 40 50 20
 * Output:
 * 30
 * Penjelasan:
 * Katak melompat dari 0 -> 1 (jarak 1, biaya |10-30|=20), lalu 1 -> 4 (jarak 3, biaya |30-20|=10).
 * Total biaya = 20 + 10 = 30.
 *
 * Test Case 2:
 * Input:
 * 3 1
 * 10 20 10
 * Output:
 * 20
 * Penjelasan:
 * Karena K = 1, katak hanya bisa melompat 1 langkah: 0 -> 1 -> 2.
 * Biaya: |10-20| + |20-10| = 10 + 10 = 20.
 *
 * Test Case 3:
 * Input:
 * 2 100
 * 10 10
 * Output:
 * 0
 * Penjelasan:
 * Langsung melompat dari 0 ke 1 dengan biaya |10-10| = 0.
 *
 * Hint 1:
 * Definisikan dp[i] = biaya minimum mencapai batu ke-i.
 *
 * Hint 2:
 * Untuk menghitung dp[i], periksa semua kemungkinan batu asal j dari 1 sampai K langkah sebelumnya:
 * dp[i] = min(dp[i - j] + |h[i] - h[i - j]|) untuk semua 1 <= j <= K asalkan i - j >= 0.
 *
 * Hint 3:
 * Kompleksitas waktu total adalah O(N * K). Dengan N = 100.000 dan K = 100, operasi maksimum
 * sekitar 10^7, yang sangat aman berjalan dalam batas waktu 2 detik.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // TODO: Implementasikan solusi DP untuk Frog 2
    // Inisialisasi dp[0] = 0 dan dp[i] = INF untuk i > 0
    // Gunakan nested loop: loop luar untuk i (1 s.d. n-1), loop dalam untuk j (1 s.d. k)

    return 0;
}
