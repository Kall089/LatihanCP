/*
============================================================
🏋️ Exercise 1: Penukaran Koin Minimum (Minimizing Coins)
============================================================
Day: 144 | Difficulty: Easy | Topic: Coin Change Minimum
Source: CSES 1634 / LeetCode 322
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis koin dengan nilai masing-masing c[0], c[1], ..., c[N-1]
dan sebuah nominal target X.
Setiap jenis koin tersedia dalam jumlah tak terbatas (boleh dipakai berkali-kali).
Tentukan jumlah koin paling sedikit yang diperlukan untuk membentuk tepat nominal X.
Jika nominal X tidak mungkin dibentuk dengan kombinasi koin yang ada, keluarkan -1.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat c[0], c[1], ..., c[N-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: jumlah koin minimum, atau -1 jika mustahil.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 0 <= X <= 1.000.000
- 1 <= c[i] <= 1.000.000

📎 SAMPLE INPUT 1:
3 11
1 5 7

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1: 11 = 5 + 5 + 1 (3 koin)]

📎 SAMPLE INPUT 2:
3 6
1 3 4

📎 SAMPLE OUTPUT 2:
2

[Penjelasan Sample 2: 6 = 3 + 3 (2 koin). Greedy akan memilih 4+1+1=3 koin yang salah!]

📎 SAMPLE INPUT 3:
2 5
2 4

📎 SAMPLE OUTPUT 3:
-1

[Penjelasan Sample 3: Semua koin genap, tidak mungkin membentuk nominal 5 ganjil]

💡 HINT:
- Inisialisasi array dp dengan ukuran (X + 1) bernilai INF.
- dp[0] = 0.
- Lakukan loop i dari 1 sampai X, lalu loop setiap koin c.
- Pastikan cek dp[i - c] != INF sebelum menambahkan 1.

🎯 Learning Goals:
- [ ] Memahami base case dp[0] = 0 dan nilai awal INF.
- [ ] Mencegah integer overflow saat dp[i - c] + 1.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
}