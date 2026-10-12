/*
============================================================
🏋️ Exercise 5: Coin Combinations II (Banyak Cara Kombinasi)
============================================================
Day: 144 | Difficulty: Medium | Topic: Counting DP (Kombinasi)
Source: CSES 1636 / LeetCode 518
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis koin positif berbeda c[0], ..., c[N-1] dan sebuah nominal target X.
Setiap jenis koin tersedia dalam jumlah tak terbatas.
Tentukan banyaknya kombinasi berbeda untuk membentuk tepat nominal X, di mana
urutan koin TIDAK diperhitungkan (misalnya susunan koin 2+3 dan 3+2 dianggap
sebagai satu kombinasi yang SAMA).

Karena jawabannya bisa sangat besar, keluarkan hasil modulo 1.000.000.007.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat c[0], c[1], ..., c[N-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: banyaknya kombinasi modulo 1.000.000.007.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 0 <= X <= 1.000.000
- 1 <= c[i] <= 1.000.000

📎 SAMPLE INPUT 1:
3 9
2 3 5

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
Hanya ada 3 kombinasi berbeda tanpa mempedulikan urutan:
1. {2, 2, 5}
2. {3, 3, 3}
3. {2, 2, 2, 3}]

📎 SAMPLE INPUT 2:
2 3
1 2

📎 SAMPLE OUTPUT 2:
2

[Penjelasan Sample 2:
Dua kombinasi: {1, 1, 1} dan {1, 2}]

📎 SAMPLE INPUT 3:
1 4
5

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3: Koin bernilai 5 tidak bisa membentuk nominal 4]

💡 HINT:
- Kunci kombinasi: Loop KOIN c di LUAR, loop nominal i di DALAM (mulai dari c ke X).
- Base case: dp[0] = 1.
- Dengan memproses koin satu per satu, setiap koin diproses dalam urutan terurut, sehingga tidak ada permutasi ganda.

🎯 Learning Goals:
- [ ] Memahami perbedaan fundamental struktur loop antara Permutasi vs Kombinasi.
- [ ] Menguasai Unbounded Knapsack untuk problem counting kombinasi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // TODO: Selesaikan Coin Combinations II (Kombinasi)
    // 1. vector<int> dp(x + 1, 0)
    // 2. dp[0] = 1
    // 3. Loop luar: setiap koin dalam c
    // 4. Loop dalam: i dari koin sampai x (loop MAJU)
    // 5. dp[i] = (dp[i] + dp[i - koin]) % MOD
    // 6. Cetak dp[x]

    return 0;
}
