/*
============================================================
🏋️ Exercise 5: Letusan Balon Karnaval (Burst Balloons)
============================================================
Day: 151 | Difficulty: Hard | Topic: Reverse Range DP
Source: LeetCode 312 (Burst Balloons) / Classic Range DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Di sebuah stan karnaval festival, terdapat N balon berjajar dari kiri ke kanan.
Balon ke-i memiliki angka skor a[i].
Kamu diminta meletuskan seluruh balon tersebut satu per satu.
Jika kamu meletuskan balon ke-i, kamu akan memperoleh koin sebanyak:
(skor balon tetangga kiri yang masih utuh) * a[i] * (skor balon tetangga kanan yang masih utuh).

Jika sudah tidak ada balon tersisa di sebelah kiri atau sebelah kanan dari balon yang diletuskan,
anggap ada balon virtual pembatas di ujung terluar dengan skor tepat 1.

Tentukan jumlah koin total MAKSIMUM yang bisa kamu kumpulkan setelah meletuskan SELURUH N balon.

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: total koin maksimum yang dapat diperoleh.

📏 CONSTRAINTS:
- 1 <= N <= 180
- 0 <= a[i] <= 100

📎 SAMPLE INPUT 1:
4
3 1 5 8

📎 SAMPLE OUTPUT 1:
167

[Penjelasan Sample 1:
Deretan balon awal: [3, 1, 5, 8] dengan batas virtual [1, 3, 1, 5, 8, 1].
1. Letuskan balon 1 (angka 1): koin = 3 * 1 * 5 = 15. Balon tersisa [3, 5, 8].
2. Letuskan balon 5 (angka 5): koin = 3 * 5 * 8 = 120. Balon tersisa [3, 8].
3. Letuskan balon 3 (angka 3): koin = 1 * 3 * 8 = 24. Balon tersisa [8].
4. Letuskan balon 8 (angka 8): koin = 1 * 8 * 1 = 8.
Total koin = 15 + 120 + 24 + 8 = 167 (Maksimum).]

📎 SAMPLE INPUT 2:
2
1 5

📎 SAMPLE OUTPUT 2:
10

[Penjelasan Sample 2:
Urutan optimal: letuskan balon 1 (koin 1 * 1 * 5 = 5), lalu balon 5 (koin 1 * 5 * 1 = 5). Total = 10.]

💡 HINT:
- Berpikir maju (balon mana yang meletus pertama) sangat sulit karena tetangga kiri dan kanan saling menyatu.
- **Balik logikanya (Reverse Range DP)**:
  Tentukan balon `k` yang menjadi balon TERAKHIR yang diletuskan di dalam sub-interval (l, r).
- Tambahkan elemen dummy 1 di kedua ujung: array `nums = [1, a[0], a[1], ..., a[n-1], 1]`.
- State: dp[l][r] = koin maksimum untuk meletuskan semua balon di dalam rentang terbuka (l, r).
- Transisi:
  dp[l][r] = max_{l < k < r} (dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r]).
- Loop luar: panjang rentang `len` dari 2 sampai n + 1.
- Jawaban akhir ada di dp[0][n + 1].

🎯 Learning Goals:
- [ ] Memahami paradigma Reverse Range DP (menentukan elemen terakhir yang diproses).
- [ ] Mengatasi ketergantungan dinamis elemen tetangga dengan menambahkan batas batas virtual.
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

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Selesaikan Reverse Range DP Burst Balloons
    // 1. Tambahkan padding 1 di indeks 0 dan n + 1
    // 2. Tabulasi dp[l][r] untuk interval terbuka (l, r)
    // 3. Cetak dp[0][n + 1]

    return 0;
}
