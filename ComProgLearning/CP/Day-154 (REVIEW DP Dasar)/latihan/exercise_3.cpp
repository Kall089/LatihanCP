/*
============================================================
🏋️ Exercise 3: Rute Hadiah dan Banyak Pemenang (Grid Max + Way Counting)
============================================================
Day: 154 | Difficulty: Hard | Topic: Grid DP + Counting Optimal Paths
Source: Review Synthesis / Classic Grid DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan labirin festival berukuran N baris dan M kolom.
Setiap sel (r, c) berisi:
- Karakter `#` : sel rintangan/tertutup yang tidak bisa dilewati.
- Bilangan bulat hadiah : nilai hadiah yang diperoleh saat menginjak sel tersebut (bisa negatif).

Perjalanan dimulai dari sel (0, 0) dan berakhir di sel (N-1, M-1).
Dari sel (r, c), kamu hanya boleh melangkah ke Kanan (r, c+1) atau ke Bawah (r+1, c).
Nilai sebuah jalur adalah JUMLAH HADIAH dari seluruh sel yang dilewati sepanjang jalur (termasuk awal dan akhir).
Dua jalur dianggap berbeda jika urutan sel yang dilewati berbeda.

Tugas kamu:
1. Hitung NILAI MAKSIMUM dari jalur yang mungkin dari (0, 0) ke (N-1, M-1).
2. Hitung BANYAK JALUR BERBEDA yang menghasilkan nilai maksimum tersebut, modulo 1.000.000.007!
Jika tujuan tidak dapat dicapai sama sekali (atau sel awal/akhir tertutup `#`), cetak `IMPOSSIBLE`.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan M.
- N baris berikutnya masing-masing berisi M token dipisahkan spasi (berupa bilangan hadiah atau `#`).

📤 OUTPUT FORMAT:
- Jika tidak ada jalur valid, cetak `IMPOSSIBLE`.
- Jika ada, cetak dua bilangan bulat dipisahkan spasi: nilai maksimum dan banyak jalur optimum modulo 1.000.000.007.

📏 CONSTRAINTS:
- 1 <= N, M <= 200
- -1.000.000.000 <= hadiah <= 1.000.000.000

📎 SAMPLE INPUT 1:
2 2
1 1
1 1

📎 SAMPLE OUTPUT 1:
3 2

[Penjelasan Sample 1:
Ada 2 jalur:
- (0,0)->(0,1)->(1,1): nilai = 1 + 1 + 1 = 3.
- (0,0)->(1,0)->(1,1): nilai = 1 + 1 + 1 = 3.
Kedua jalur sama-sama menghasilkan nilai 3. Total jalur optimal = 2.]

📎 SAMPLE INPUT 2:
1 1
-7

📎 SAMPLE OUTPUT 2:
-7 1

[Penjelasan Sample 2:
Hanya 1 sel bernilai -7. Jawabannya -7 dan 1 jalur.]

📎 SAMPLE INPUT 3:
2 2
1 #
# 1

📎 SAMPLE OUTPUT 3:
IMPOSSIBLE

[Penjelasan Sample 3:
Semua tetangga sel (0,0) terhalang oleh `#`, tujuan tidak dapat dicapai.]

💡 HINT:
- Simpan dua tabel 2D:
  1. `best[r][c]`: nilai maksimum untuk mencapai sel (r, c).
  2. `ways[r][c]`: banyak jalur yang menghasilkan nilai `best[r][c]`.
- Inisialisasi:
  - `best` dengan nilai sangat negatif `-INF`.
  - `ways` dengan 0.
- Base case:
  - Jika sel (0, 0) bukan `#`: `best[0][0] = hadiah`, `ways[0][0] = 1`.
- Transisi dari sel atas (r - 1, c) dan sel kiri (r, c - 1):
  - Misal kandidat datang dari tetangga dengan total nilai `cand = best[tetangga] + hadiah[r][c]`:
    - Jika `cand > best[r][c]`: nilai baru lebih baik!
      `best[r][c] = cand`, `ways[r][c] = ways[tetangga]`.
    - Jika `cand == best[r][c]`: terjadi SERI!
      `ways[r][c] = (ways[r][c] + ways[tetangga]) % MOD`.
    - Jika `cand < best[r][c]`: abaikan.
- Cek apakah `best[N-1][M-1] == -INF`.

🎯 Learning Goals:
- [ ] Menggabungkan optimasi nilai ekstrem (min/max) dengan penghitungan banyak jalur (*counting*).
- [ ] Menerapkan aturan pembaruan state berpasangan (nilai terbaik, jumlah jalur) dengan penanganan seri (*tie-break*).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan Grid Max Path + Way Counting

    return 0;
}
