#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 1: Lompat Katak Dasar (Frog 1 - AtCoder DP-A)
 *
 * Seekor katak berada di batu ke-1 (indeks 0) dan ingin mencapai batu ke-N (indeks N-1).
 * Terdapat N batu dengan tinggi masing-masing h[0], h[1], ..., h[N-1].
 * Dari batu i, katak hanya boleh melompat ke batu (i + 1) atau ke batu (i + 2).
 * Biaya energi yang dikeluarkan untuk melompat dari batu i ke batu j adalah |h[i] - h[j]|.
 * Hitung total biaya energi minimum yang dibutuhkan katak untuk mencapai batu ke-N.
 *
 * Coba selesaikan soal ini dengan DUA cara:
 * 1. Top-Down (Rekursi + Memoisasi)
 * 2. Bottom-Up (Tabulasi Iteratif)
 *
 * Format Input:
 * Baris pertama berisi satu bilangan bulat N.
 * Baris kedua berisi N bilangan bulat h[0], h[1], ..., h[N-1].
 *
 * Format Output:
 * Satu bilangan bulat: total biaya energi minimum.
 *
 * Batasan:
 * 2 <= N <= 100.000
 * 1 <= h[i] <= 10.000
 *
 * Test Case 1:
 * Input:
 * 4
 * 10 30 40 20
 * Output:
 * 30
 * Penjelasan:
 * Jalur optimal: batu 0 -> batu 1 -> batu 3.
 * Biaya: |10 - 30| + |30 - 20| = 20 + 10 = 30.
 *
 * Test Case 2:
 * Input:
 * 2
 * 10 10
 * Output:
 * 0
 * Penjelasan:
 * Hanya ada 1 lompatan langsung dari 0 ke 1 dengan biaya |10 - 10| = 0.
 *
 * Test Case 3:
 * Input:
 * 6
 * 30 10 60 10 60 50
 * Output:
 * 40
 * Penjelasan:
 * Jalur optimal: 0 -> 2 -> 4 -> 5.
 * Biaya: |30 - 60| + |60 - 60| + |60 - 50| = 30 + 0 + 10 = 40.
 *
 * Hint 1:
 * Definisikan dp[i] = biaya minimum untuk mencapai batu ke-i.
 *
 * Hint 2:
 * Untuk mencapai batu i (i >= 2), katak bisa datang dari batu i-1 atau i-2.
 * Maka dp[i] = min(dp[i-1] + |h[i] - h[i-1]|, dp[i-2] + |h[i] - h[i-2]|).
 *
 * Hint 3:
 * Base case: dp[0] = 0 (berada di titik awal tidak butuh biaya).
 * dp[1] = |h[1] - h[0]|.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // TODO: Implementasikan solusi DP (coba bandingkan Top-Down vs Bottom-Up)
    // Jangan lupa inisialisasi tabel / memo dengan nilai INF untuk minimisasi

    return 0;
}