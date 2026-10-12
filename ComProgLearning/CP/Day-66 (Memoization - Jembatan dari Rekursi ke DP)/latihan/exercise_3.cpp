/*
============================================================
🏋️ Exercise 3: Denah Festival Batik (Grid Paths with Obstacles Top-Down)
============================================================
Day: 066 | Difficulty: Medium | Topic: 2D Top-Down Memoization
Source: Classic Grid DP / Review
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Denah area Festival Batik berbentuk sebuah kisi berukuran N baris dan M kolom.
Setiap petak (r, c) ditandai dengan:
- Karakter `.` : petak terbuka yang boleh dilalui.
- Karakter `#` : stan tertutup / rintangan yang tidak boleh dilewati.

Pengunjung mulai dari petak kiri atas (0, 0) dan ingin menuju stan cinderamata utama di petak
kanan bawah (N-1, M-1).
Dari petak (r, c), pengunjung hanya boleh berjalan satu petak ke KANAN (r, c+1) atau satu petak ke BAWAH (r+1, c).

Hitung BANYAK JALUR BERBEDA dari (0, 0) ke (N-1, M-1), modulo 1.000.000.007!
Jika petak awal (0, 0) atau petak akhir (N-1, M-1) tertutup `#`, maka tidak ada jalur yang mungkin (cetak 0).

Selesaikan dengan pendekatan REKURSIF DENGAN MEMOISASI 2D (Top-Down)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan M.
- N baris berikutnya masing-masing berisi sebuah string sepanjang M karakter (`.` atau `#`).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: banyak jalur berbeda modulo 1.000.000.007.

📏 CONSTRAINTS:
- 1 <= N, M <= 100
- Karakter hanya `.` dan `#`

📎 SAMPLE INPUT 1:
3 3
...
.#.
...

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Ada 2 jalur menghindari rintangan di tengah:
1. Kanan -> Kanan -> Bawah -> Bawah
2. Bawah -> Bawah -> Kanan -> Kanan]

📎 SAMPLE INPUT 2:
1 1
.

📎 SAMPLE OUTPUT 2:
1

[Penjelasan Sample 2:
Grid 1x1 terbuka, hanya ada 1 jalur (sudah di tujuan).]

📎 SAMPLE INPUT 3:
1 1
#

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Petak tujuan tertutup `#`, tidak ada jalur.]

💡 HINT:
- Gunakan fungsi rekursif 2D:
  `solve(r, c)`: banyak jalur dari sel (r, c) menuju sel tujuan (N-1, M-1).
- Kasus Dasar:
  - `if (r >= N || c >= M) return 0;` (keluar dari grid)
  - `if (grid[r][c] == '#') return 0;` (menabrak rintangan)
  - `if (r == N - 1 && c == M - 1) return 1;` (mencapai tujuan)
- Cek Memoisasi:
  - `if (seen[r][c]) return memo[r][c];`
  - `seen[r][c] = true;`
- Transisi:
  - Melangkah ke bawah: `solve(r + 1, c)`
  - Melangkah ke kanan: `solve(r, c + 1)`
  - `return memo[r][c] = (solve(r + 1, c) + solve(r, c + 1)) % MOD;`

🎯 Learning Goals:
- [ ] Menerapkan memoisasi pada grid dua dimensi dengan status koordinat (r, c).
- [ ] Menangani kasus khusus batas koordinat dan validitas sel awal/akhir.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization

    return 0;
}
