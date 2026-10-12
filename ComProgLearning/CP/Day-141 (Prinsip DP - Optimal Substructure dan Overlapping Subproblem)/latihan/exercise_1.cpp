/*
============================================================
🏋️ Exercise 1: Naik Tangga
============================================================
Day: 85 | Difficulty: Easy
Topic: DP 1D — pola "berapa cara"
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N anak tangga. Sekali melangkah, kamu boleh naik 1 atau 2 anak tangga.
Hitung ada berapa cara berbeda untuk mencapai anak tangga ke-N,
dimulai dari tanah (tangga ke-0).
Karena jawabannya bisa sangat besar, cetak hasilnya modulo 1000000007.

Contoh untuk N = 3, ada 3 cara: (1+1+1), (1+2), dan (2+1).

📥 INPUT FORMAT:
- Satu baris berisi bilangan N

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya cara modulo 1000000007.

📏 CONSTRAINTS:
- 1 <= N <= 10^6

📎 SAMPLE INPUT 1:
3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
5

📎 SAMPLE OUTPUT 2:
8

📎 SAMPLE INPUT 3:
1

📎 SAMPLE OUTPUT 3:
1

💡 HINT:
- Pikirkan LANGKAH TERAKHIR menuju tangga ke-i. Hanya ada dua kemungkinan:
  dari tangga (i-1) dengan langkah 1, atau dari (i-2) dengan langkah 2.
- Jadi dp[i] = dp[i-1] + dp[i-2].
- Basisnya dp[0] = 1 (ada satu cara untuk "sudah sampai": tidak melangkah).
- Jangan lupa modulo di setiap penjumlahan.

🎯 Learning Goals:
- [ ] Merancang state dan transisi dari nol
- [ ] Menentukan basis yang benar
- [ ] Menerapkan modulo pada DP penghitungan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main()
{
  int n;
  cin >> n;

  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; i++)
  {

    if (i >= 1)
    {
      dp[i] = (dp[i] + dp[i - 1]) % MOD;
    }

    if (i >= 2)
    {
      dp[i] = (dp[i] + dp[i - 2]) % MOD;
    }
  }

  cout << dp[n];
}