/*
============================================================
🏋️ Exercise 4: Maximum Submatrix Sum (Ukuran Bebas)
============================================================
Day: 30 | Difficulty: Medium-Hard
Topic: 2D Kadane / Prefix Sum 2D + Compression
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan matriks N × M yang berisi integer positif, negatif, atau nol.
Cari jumlah elemen maksimum dari submatriks APAPUN (ukuran 1×1 hingga N×M).
Setidaknya satu sel harus dipilih!

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan M (1 ≤ N, M ≤ 300)
- N baris berikutnya: M integer A[i][j] (-10^5 ≤ A[i][j] ≤ 10^5)

📤 OUTPUT FORMAT:
- Cetak satu integer: jumlah elemen maksimum dari submatriks yang mungkin.

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 300
- -10^5 ≤ A[i][j] ≤ 10^5

📎 SAMPLE INPUT 1:
4 4
0 -2 -7 0
9 2 -6 2
-4 1 5 4
-1 8 0 -2

📎 SAMPLE OUTPUT 1:
15

📎 EXPLANATION 1:
Submatriks dengan jumlah maksimum adalah dari baris 2..4 dan kolom 2..4:
[ 2 -6  2]
[ 1  5  4]
[ 8  0 -2] → 2 - 6 + 2 + 1 + 5 + 4 + 8 + 0 - 2 = 15.

💡 HINT:
- Dengan N, M ≤ 300, solusi O(N^3) atau O(N^2 * M) akan cukup cepat (300^3 = 2.7 × 10^7 operasi).
- Tentukan baris atas r1 (1..N) dan baris bawah r2 (r1..N).
- Untuk pasangan (r1, r2) ini, kompresi kolom j menjadi col_sum[j] = psum(r1, j, r2, j).
- Jalankan algoritma Kadane 1D pada array col_sum[1..M] untuk mencari subarray maksimum dalam O(M)!
- Total kompleksitas: O(N^2 × M).

🎯 Learning Goals:
- [ ] Mengombinasikan Prefix Sum 2D dengan Algoritma Kadane 1D
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Build psum 2D

    // TODO: Fix baris r1 (1..N) dan baris r2 (r1..N)
    // Lalu jalankan Kadane 1D pada kompresi kolom untuk mendapatkan O(N^2 * M)

    return 0;
}
