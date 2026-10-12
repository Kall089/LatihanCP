/*
============================================================
🏋️ Exercise 4: Koin Minimum
============================================================
Day: 85 | Difficulty: Medium
Topic: DP 1D — pola "minimal langkah"
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada K jenis pecahan koin dengan nilai berbeda, masing-masing tersedia
tak terbatas. Tentukan jumlah koin MINIMAL yang dibutuhkan untuk
membentuk nilai tepat sebesar T.
Jika nilai T tidak mungkin dibentuk, cetak -1.

Contoh: dengan koin {1, 3, 4} dan target 6, jawabannya 2 (yaitu 3 + 3).
Perhatikan bahwa mengambil koin terbesar dulu (4 + 1 + 1 = 3 koin)
justru TIDAK optimal.

📥 INPUT FORMAT:
- Baris pertama: dua bilangan K dan T
- Baris kedua: K bilangan nilai koin

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah koin minimal, atau -1 jika mustahil.

📏 CONSTRAINTS:
- 1 <= K <= 100
- 1 <= T <= 10^6
- 1 <= nilai koin <= 10^6

📎 SAMPLE INPUT 1:
3 6
1 3 4

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
2 7
2 4

📎 SAMPLE OUTPUT 2:
-1

📎 SAMPLE INPUT 3:
3 11
1 5 7

📎 SAMPLE OUTPUT 3:
3

💡 HINT:
- dp[v] = koin minimal untuk membentuk nilai v.
- Untuk membentuk v, koin TERAKHIR yang dipakai bisa jenis apa saja.
  Kalau koin terakhirnya bernilai k, sisanya adalah dp[v - k].
- dp[v] = min(dp[v - k] + 1) untuk semua koin k yang <= v.
- Basis: dp[0] = 0. Tandai yang belum bisa dicapai dengan nilai besar (INF).

🎯 Learning Goals:
- [ ] Menerapkan pola minimal langkah
- [ ] Menangani kasus tidak mungkin dengan benar
- [ ] Melihat bukti bahwa greedy gagal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
  int n, T;
  cin >> n >> T;

  vector<int> coin(n);

  for (int i = 0; i < n; i++)
  {
    cin >> coin[i];
  }

  vector<int> dp(T + 1, INF);
  dp[0] = 0;

  for (int i = 0; i <= T; i++)
  {
    for (int x : coin)
    {
      if (i >= x && dp[i - x] != INF)
      {
        dp[i] = min(dp[i], dp[i - x] + 1);
      }
    }
  }

  if (dp[T] != INF)
  {
    cout << dp[T];
  }
  else
  {
    cout << -1;
  }
}