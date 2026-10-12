/*
============================================================
🏋️ Exercise 6: Rekonstruksi Subsekuens Naik Terpanjang (LIS Reconstruction)
============================================================
Day: 152 | Difficulty: Medium | Topic: 1D DP + Parent Array Tracking
Source: Classic DP / LeetCode 300 Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array bilangan bulat a berukuran N.
Sebuah subsekuens dari array a adalah barisan elemen yang diambil tanpa mengubah urutan aslinya.
Subsekuens naik ketat (Strictly Increasing Subsequence) adalah subsekuens di mana setiap elemen
lebih besar secara ketat daripada elemen sebelumnya: a[i_1] < a[i_2] < ... < a[i_k] dengan i_1 < i_2 < ... < i_k.

Tentukan:
1. Di baris pertama: panjang dari Subsekuens Naik Terpanjang (Longest Increasing Subsequence - LIS).
2. Di baris kedua: elemen-elemen konkret dari LIS tersebut, dipisahkan oleh spasi.

Jika terdapat lebih dari satu LIS dengan panjang maksimum yang sama, kamu boleh mencetak salah satu yang valid.

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Baris pertama: satu bilangan bulat, panjang LIS.
- Baris kedua: deretan elemen LIS dipisahkan spasi.

📏 CONSTRAINTS:
- 1 <= N <= 2.000
- -1.000.000.000 <= a[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
6
10 9 2 5 3 7

📎 SAMPLE OUTPUT 1:
3
2 5 7

[Penjelasan Sample 1:
LIS dengan panjang 3: [2, 5, 7] atau [2, 3, 7]. Salah satu jawaban valid diterima.]

📎 SAMPLE INPUT 2:
6
0 1 0 3 2 3

📎 SAMPLE OUTPUT 2:
4
0 1 2 3

📎 SAMPLE INPUT 3:
5
7 7 7 7 7

📎 SAMPLE OUTPUT 3:
1
7

[Penjelasan Sample 3:
Karena harus naik KETAT (<), subsekuens terpanjang hanya berpanjang 1.]

💡 HINT:
- Gunakan Pola 1 (Parent Array Tracking):
  `dp[i]` = panjang LIS terpanjang yang BERAKHIR di indeks i.
  `parent[i]` = indeks elemen sebelum i dalam LIS tersebut (inisialisasi -1).
- Untuk setiap i dari 0 s.d. N-1:
  dp[i] = 1
  Untuk setiap j dari 0 s.d. i-1:
    Jika a[j] < a[i] dan dp[j] + 1 > dp[i]:
      dp[i] = dp[j] + 1
      parent[i] = j
- Cari indeks `best_idx` dengan dp[best_idx] maksimum.
- Telusuri mundur dari `best_idx` menggunakan array parent, lalu balikkan hasil deretan elemen.

🎯 Learning Goals:
- [ ] Menguasai Pola Parent Array untuk merekonstruksi jawaban dari DP 1D.
- [ ] Menghubungkan backtracking rantai pointer `parent[i]` dengan struktur LIS.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Selesaikan LIS Reconstruction dengan Parent Array
    // 1. Tabulasi dp[i] dan catat parent[i]
    // 2. Cari best_idx dengan dp maksimum
    // 3. Backtrack parent pointer dan cetak elemen asli

    return 0;
}
