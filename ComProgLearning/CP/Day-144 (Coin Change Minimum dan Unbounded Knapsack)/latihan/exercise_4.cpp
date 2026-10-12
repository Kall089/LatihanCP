/*
============================================================
🏋️ Exercise 4: Coin Combinations I (Banyak Cara Permutasi)
============================================================
Day: 144 | Difficulty: Medium | Topic: Counting DP (Permutasi)
Source: CSES 1635
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis koin positif berbeda c[0], ..., c[N-1] dan sebuah nominal target X.
Setiap jenis koin tersedia dalam jumlah tak terbatas.
Tentukan banyaknya cara berbeda untuk membentuk tepat nominal X, di mana
urutan koin diperhitungkan (misalnya susunan koin 2+3 dan 3+2 dianggap sebagai
dua cara yang berbeda).

Karena jawabannya bisa sangat besar, keluarkan hasil modulo 1.000.000.007.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat c[0], c[1], ..., c[N-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: banyaknya cara modulo 1.000.000.007.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 0 <= X <= 1.000.000
- 1 <= c[i] <= 1.000.000

📎 SAMPLE INPUT 1:
3 9
2 3 5

📎 SAMPLE OUTPUT 1:
8

[Penjelasan Sample 1:
Ada 8 susunan yang menghasilkan total 9:
2+2+5, 2+5+2, 5+2+2, 3+3+3, 2+2+2+3, 2+2+3+2, 2+3+2+2, 3+2+2+2]

📎 SAMPLE INPUT 2:
2 3
1 2

📎 SAMPLE OUTPUT 2:
3

[Penjelasan Sample 2:
Tiga cara: 1+1+1, 1+2, 2+1]

📎 SAMPLE INPUT 3:
1 4
5

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3: Koin 5 tidak bisa membentuk nominal 4]

💡 HINT:
- Kunci permutasi: Loop nominal i di LUAR, loop koin c di DALAM.
- Base case: dp[0] = 1 (nominal 0 dibentuk dengan 1 cara, yaitu tanpa koin).
- Setiap i, dp[i] = (dp[i] + dp[i - c]) % MOD untuk setiap c <= i.

🎯 Learning Goals:
- [ ] Memahami mengapa loop nominal di luar menghasilkan permutasi (urutan berbeda).
- [ ] Menguasai operasi aritmetika modulo 10^9 + 7 pada counting DP.
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

    // TODO: Selesaikan Coin Combinations I (Permutasi)
    // 1. vector<int> dp(x + 1, 0)
    // 2. dp[0] = 1
    // 3. Loop luar: i dari 1 sampai x
    // 4. Loop dalam: setiap koin dalam c
    // 5. Jika i >= coin, dp[i] = (dp[i] + dp[i - coin]) % MOD
    // 6. Cetak dp[x]

    return 0;
}
