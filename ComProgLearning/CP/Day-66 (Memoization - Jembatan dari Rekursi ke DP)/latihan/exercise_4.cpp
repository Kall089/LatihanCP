/*
============================================================
🏋️ Exercise 4: Pembagian Harta Warisan (0/1 Knapsack Top-Down)
============================================================
Day: 066 | Difficulty: Medium | Topic: 2D Top-Down Memoization
Source: Classic Knapsack / Top-Down Paradigm
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N barang antik warisan keluarga. Barang ke-i memiliki bobot w[i] dan nilai estetika v[i].
Sebuah peti kayu kuno hanya mampu memuat barang dengan total bobot tidak lebih dari W.
Setiap barang hanya boleh dimasukkan ke dalam peti paling banyak satu kali (boleh dilewatkan).

Tentukan TOTAL NILAI ESTETIKA MAKSIMUM yang dapat dimuat ke dalam peti!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: nilai estetika maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 300
- 0 <= W <= 2.000
- 1 <= w[i] <= 2.000
- 0 <= v[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 4
2 3
3 4
4 5

📎 SAMPLE OUTPUT 1:
7

[Penjelasan Sample 1:
Pilih barang 0 (bobot 2, nilai 3) dan barang 1 (bobot 3, tidak muat jika digabung: 2+3=5 > 4).
Pilihan yang muat:
- Barang 0 saja: nilai 3
- Barang 1 saja: nilai 4
- Barang 2 saja: nilai 5
- Barang 0 dan barang ... tidak ada yang muat berdua kecuali kapasitas >= 5.
Maka maksimum adalah barang 2 (nilai 5)?
Tunggu: barang 0 (w=2, v=3), barang 1 (w=3, v=4), barang 2 (w=4, v=5).
Nilai maksimum kapasitas 4 adalah barang 2 (nilai 5) atau barang 0 (nilai 3).
Maka nilai maksimum = 5!]

📎 SAMPLE INPUT 2:
4 5
1 2
2 4
3 7
2 5

📎 SAMPLE OUTPUT 2:
12

[Penjelasan Sample 2:
Pilih barang 1 (w=2, v=4), barang 3 (w=2, v=5), barang 0 (w=1, v=2) -> total w = 5, total v = 11.
Atau pilih barang 2 (w=3, v=7) dan barang 3 (w=2, v=5) -> total w = 5, total v = 12!]

💡 HINT:
- Definisikan fungsi rekursif:
  `solve(i, s)`: nilai maksimum dari barang-barang indeks i..N-1 dengan kapasitas tersisa s.
- Kasus Dasar:
  - `if (i == N || s == 0) return 0;`
- Cek Memoisasi:
  - `if (memo[i][s] != -1) return memo[i][s];`
- Pilihan:
  1. Lewatkan barang i: `solve(i + 1, s)`
  2. Ambil barang i (jika `w[i] <= s`): `v[i] + solve(i + 1, s - w[i])`
  - `return memo[i][s] = max(opsi1, opsi2);`

🎯 Learning Goals:
- [ ] Memahami cara merancang fungsi rekursif top-down untuk 0/1 Knapsack.
- [ ] Membedakan parameter indeks barang dan sisa kapasitas dalam tabel memo 2D.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization

    return 0;
}
