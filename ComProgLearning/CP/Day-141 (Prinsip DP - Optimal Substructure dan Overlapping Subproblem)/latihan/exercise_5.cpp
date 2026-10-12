/*
============================================================
🏋️ Exercise 5: Banyaknya Cara Menyusun Koin
============================================================
Day: 85 | Difficulty: Medium-Hard
Topic: DP 1D — kombinasi vs permutasi
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada K jenis pecahan koin, masing-masing tersedia tak terbatas.
Hitung ada berapa CARA BERBEDA untuk membentuk nilai tepat T.
Dua susunan dianggap SAMA jika memakai koin yang sama banyaknya,
walaupun urutan pengambilannya berbeda. Jadi {1, 2} dan {2, 1}
dihitung sebagai SATU cara.
Cetak jawabannya modulo 1000000007.

Contoh: koin {1, 2, 5} dengan target 5 menghasilkan 4 cara:
(1+1+1+1+1), (1+1+1+2), (1+2+2), dan (5).

📥 INPUT FORMAT:
- Baris pertama: dua bilangan K dan T
- Baris kedua: K bilangan nilai koin

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya cara modulo 1000000007.

📏 CONSTRAINTS:
- 1 <= K <= 100
- 1 <= T <= 10^6

📎 SAMPLE INPUT 1:
3 5
1 2 5

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
2 4
1 2

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
1 7
3

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Ini soal PENGHITUNGAN, jadi transisinya menjumlahkan, bukan mengambil minimum.
- KUNCI: urutan loop menentukan arti jawabannya!
  * Koin di loop LUAR  -> menghitung KOMBINASI ({1,2} sama dengan {2,1})
  * Nilai di loop LUAR -> menghitung PERMUTASI ({1,2} beda dengan {2,1})
- Soal ini meminta kombinasi, jadi taruh koin di loop luar.

🎯 Learning Goals:
- [ ] Membedakan kombinasi dan permutasi pada DP
- [ ] Menyadari urutan loop mengubah arti jawaban
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int k, T;
  cin >> k >> T;

  vector<int> koin(k);

  for (int i = 0; i < k; i++)
  {
    cin >> koin[i];
  }

  vector<int> dp(T + 1, 0);

  dp[0] = 1;

  for (int k : koin)
  {
    for (int v = k; v <= T; v++)
    {
      dp[v] = (dp[v - k] + dp[v]);
    }
  }

  cout << dp[T];
}