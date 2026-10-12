/*
============================================================
🏋️ Exercise 6: Perkalian Potongan Angka Maksimum (Integer Break Top-Down)
============================================================
Day: 066 | Difficulty: Medium | Topic: 1D Top-Down Memoization
Source: LeetCode 343 / Classic Math-DP Top-Down
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah bilangan bulat positif N.
Kamu harus membagi N menjadi penjumlahan k bilangan bulat positif:
`N = a_1 + a_2 + ... + a_k` dengan k >= 2 (artinya harus dibagi menjadi minimal 2 bilangan).

Tentukan HASIL KALI MAKSIMUM dari bilangan-bilangan tersebut:
`max(a_1 * a_2 * ... * a_k)`.

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

📥 INPUT FORMAT:
- Satu baris berisi satu bilangan bulat N.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: hasil perkalian maksimum.

📏 CONSTRAINTS:
- 2 <= N <= 60

📎 SAMPLE INPUT 1:
2

📎 SAMPLE OUTPUT 1:
1

[Penjelasan Sample 1:
2 hanya bisa dibagi menjadi 1 + 1. Hasil kali = 1 * 1 = 1.]

📎 SAMPLE INPUT 2:
10

📎 SAMPLE OUTPUT 2:
36

[Penjelasan Sample 2:
10 dapat dibagi menjadi 3 + 3 + 4. Hasil kali = 3 * 3 * 4 = 36.]

📎 SAMPLE INPUT 3:
5

📎 SAMPLE OUTPUT 3:
6

[Penjelasan Sample 3:
5 dapat dibagi menjadi 2 + 3. Hasil kali = 2 * 3 = 6.]

💡 HINT:
- Definisikan fungsi rekursif `solve(rem)`:
  Hasil kali maksimum untuk memecah sisa bilangan `rem` menjadi satu atau lebih potongan.
- Perhatikan bedanya:
  Untuk bilangan awal `N`, kita WAJIB memotong setidaknya menjadi 2 bagian.
  Namun untuk submasalah `rem < N`, kita punya opsi:
  - Tidak memotong lagi (mengambil nilai `rem` itu sendiri).
  - Atau memotong lagi menjadi `i` dan memecah `rem - i`: `i * solve(rem - i)`.
- Maka untuk potongan pertama sebesar `i` (1 <= i < rem):
  `solve(rem) = max_{1 <= i < rem} (max(i * (rem - i), i * solve(rem - i)))`.
- Memoisasi 1D: `memo[rem]`.

🎯 Learning Goals:
- [ ] Memahami penanganan syarat "minimal 2 potongan" dalam rekursi top-down.
- [ ] Menerapkan pencarian opsi potongan terbaik secara rekursif dengan cache.
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

    // TODO: Selesaikan dengan 1D top-down memoization

    return 0;
}
