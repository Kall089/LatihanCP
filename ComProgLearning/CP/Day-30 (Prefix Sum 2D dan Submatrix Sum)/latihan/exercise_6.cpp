/*
============================================================
🏋️ Exercise 6: Count Submatrices with Target Sum K
============================================================
Day: 30 | Difficulty: Contest-Level / Hard
Topic: Prefix Sum 2D + Hashmap (Row Compression)
Time Limit: 1.5 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan matriks N × M dan sebuah target K.
Hitung berapa banyak submatriks (r1, c1, r2, c2) sedemikian rupa sehingga
jumlah seluruh elemen di dalam submatriks tersebut tepat sama dengan K!

(1 ≤ r1 ≤ r2 ≤ N dan 1 ≤ c1 ≤ c2 ≤ M)

📥 INPUT FORMAT:
- Baris pertama: N, M, K (1 ≤ N, M ≤ 300, -10^9 ≤ K ≤ 10^9)
- N baris berikutnya: M integer A[i][j] (-1000 ≤ A[i][j] ≤ 1000)

📤 OUTPUT FORMAT:
- Cetak satu integer: banyaknya submatriks yang jumlahnya sama dengan K.

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 300
- -1000 ≤ A[i][j] ≤ 1000
- -10^9 ≤ K ≤ 10^9

📎 SAMPLE INPUT 1:
3 3 5
1 2 3
4 5 6
7 8 9

📎 SAMPLE OUTPUT 1:
2

📎 EXPLANATION 1:
Submatriks yang memiliki jumlah = 5:
1. Submatriks (1,2) ke (1,3) -> 2 + 3 = 5
2. Submatriks (2,2) ke (2,2) -> 5 = 5
Total = 2 submatriks.

💡 HINT:
- Brute force 4 titik O(N^2 × M^2) -> TLE (300^4 ≈ 8.1 × 10^9).
- Kita bisa mengoptimalkan menjadi O(N^2 × M) dengan teknik kompresi baris:
  1. Fixkan baris atas r1 (1..N) dan baris bawah r2 (r1..N).
  2. Untuk pasangan (r1, r2), kita memiliki array 1D berukuran M di mana col[j] = sum dari A[r1..r2][j].
  3. Masalah berubah menjadi: "Hitung berapa subarray di col[1..M] yang jumlahnya = K".
  4. Ini bisa diselesaikan dalam O(M) menggunakan prefix sum 1D + hash map (std::map / unordered_map).
- Total Kompleksitas: O(N^2 × M log M) atau O(N^2 × M).

🎯 Learning Goals:
- [ ] Menggabungkan teknik kompresi dimensi 2D ke 1D dengan prefix sum + hash map
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long target_k;
    if (!(cin >> n >> m >> target_k)) return 0;

    // TODO: Build psum 2D

    // TODO: Iterasi r1 (1..N) dan r2 (r1..N)
    // Untuk tiap pasang r1, r2, jalankan algoritma Subarray Sum = K menggunakan Hash Map

    return 0;
}
