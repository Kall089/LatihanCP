/*
============================================================
🏋️ Exercise 2: Arah Loop yang Menentukan
============================================================
Day: 145 | Difficulty: Easy
Topic: 0/1 versus unbounded
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis berat; berat ke-i punya berat w[i] dan nilai v[i], serta
kapasitas tas W.
Cetak DUA bilangan:
- nilai maksimum kalau setiap jenis berat hanya boleh diambil PALING BANYAK
  SEKALI, dan
- nilai maksimum kalau setiap jenis berat boleh diambil BERAPA KALI PUN.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Dua bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^5
- 1 <= w[i] <= W
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3 5
3 3
2 4
4 2

📎 SAMPLE OUTPUT 1:
7 8

📎 SAMPLE INPUT 2:
1 4
2 3

📎 SAMPLE OUTPUT 2:
3 6

💡 HINT: Kedua jawaban bisa dihitung dengan array satu dimensi dan rekurens
         yang HURUF PER HURUF SAMA. Yang membedakan hanya satu hal, dan itu
         adalah hal terpenting dari seluruh materi hari ini.
         Pikirkan: saat kamu memperbarui dp[c] dengan membaca dp[c - w[i]],
         apakah nilai yang kamu baca itu SUDAH memuat berat ke-i atau
         BELUM? Jawabannya bergantung pada urutan kamu menyapu c.
         Sampel 2 dirancang agar perbedaannya sangat jelas: dengan satu
         berat berbobot 2 dan kapasitas 4, berapa kali berat itu bisa
         masuk pada masing-masing aturan?
         Perhatikan juga tipe data untuk nilainya.

🎯 Learning Goals:
- [ ] Menemukan sendiri kenapa arah loop menentukan 0/1 vs unbounded
- [ ] Menulis dua varian dengan satu template
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, W;
  cin >> n >> W;

  vector<int> berat(n);
  vector<int> nilai(n);

  for (int i = 1; i <= n; i++)
  {
    cin >> berat[i];
    cin >> nilai[i];
  }

  vector<vector<int>> dp_a(n + 1, vector<int>(W + 1, 0));
  vector<vector<int>> dp_b(n + 1, vector<int>(W + 1, 0));

  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= W; j++)
    {
      dp_a[i][j] = dp_a[i - 1][j];
      dp_b[i][j] = dp_b[i - 1][j];
      if (berat[i] <= j)
      {
        dp_a[i][j] = max(dp_a[i][j], dp_a[i - 1][j - berat[i]] + nilai[i]);
        dp_b[i][j] = max(dp_b[i][j], dp_b[i][j - berat[i]] + nilai[i]);
      }
    }
  }

  cout << dp_a[n][W] << " " << dp_b[n][W];
}